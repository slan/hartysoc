// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

#include <stdarg.h>
#include <stdint.h>

extern uint32_t time();
extern uint32_t insn();

#ifdef USE_MYSTDLIB
extern char *malloc();
extern int printf(const char *format, ...);

extern void *memcpy(void *dest, const void *src, long n);
extern char *strcpy(char *dest, const char *src);
extern int strcmp(const char *s1, const char *s2);

char heap_memory[1024];
int heap_memory_used = 0;
#endif

uint32_t time()
{
	int cycles;
	asm volatile ("rdcycle %0" : "=r"(cycles));
	// printf("[time() -> %d]", cycles);
	return cycles;
}

uint32_t insn()
{
	int insns;
	asm volatile ("rdinstret %0" : "=r"(insns));
	// printf("[insn() -> %d]", insns);
	return insns;
}

#ifdef USE_MYSTDLIB
char *malloc(int size)
{
	char *p = heap_memory + heap_memory_used;
	// printf("[malloc(%d) -> %d (%d..%d)]", size, (int)p, heap_memory_used, heap_memory_used + size);
	heap_memory_used += size;
	if (heap_memory_used > 1024)
		asm volatile ("ebreak");
	return p;
}

static int printf_c(int c)
{
    volatile char* uart = (char*)0x10000000;
    *uart = c;
	return 1;
}

static int printf_s(char *p)
{
	char* p0 = p;
	while (*p)
		printf_c(*(p++));
	return p-p0;
}

static int printf_u(unsigned int n)
{
	char buffer[32];
	char *p = buffer;
	unsigned q, r;
	while (n || p == buffer) {
		q = (n >> 1) + (n >> 2);
		q = q + (q >> 4);
		q = q + (q >> 8);
		q = q + (q >> 16);
		q = q >> 3;
		r = n - (((q << 2) + q) << 1);
		*(p++) = '0' + (r > 9 ? r - 10 : r);
		n = q + (r > 9);
	}
	char* p0 = p;
	while (p != buffer)
		printf_c(*(--p));
	return p0-p;
}

static int printf_d(int val)
{
	if (val < 0) {
		printf_c('-');
		return 1 + printf_u(-val);
	} else {
		return printf_u(val);
	}
}

static int printf_x(unsigned int val)
{
	char buffer[32];
	char *p = buffer;
	while (val || p == buffer) {
		int mod = val & 0xf;
		*(p++) = (mod<10?'0':'A'-10)+mod;
		val = val >> 4;
	}
	char* p0 = p;
	while (p != buffer)
		printf_c(*(--p));
	return p0 - p;
}

int printf(const char *format, ...)
{
	int i;
	va_list ap;

	va_start(ap, format);

	int ret = 0;
	for (i = 0; format[i]; i++)
		if (format[i] == '%') {
			while (format[++i]) {
				if (format[i] == 'c') {
					ret += printf_c(va_arg(ap,int));
					break;
				}
				if (format[i] == 's') {
					ret += printf_s(va_arg(ap,char*));
					break;
				}
				if (format[i] == 'd') {
					ret += printf_d(va_arg(ap,int));
					break;
				}
				if (format[i] == 'u') {
					ret += printf_u(va_arg(ap,unsigned int));
					break;
				}
				if (format[i] == 'x') {
					ret += printf_x(va_arg(ap,unsigned int));
					break;
				}
			}
		} else {
			ret += printf_c(format[i]);
		}

	va_end(ap);
	return ret;
}

void *memcpy(void *aa, const void *bb, long n)
{
	// printf("**MEMCPY**\n");
	char *a = aa;
	const char *b = bb;
	while (n--) *(a++) = *(b++);
	return aa;
}

char *strcpy(char* dst, const char* src)
{
	char *r = dst;

	while ((((uint32_t)dst | (uint32_t)src) & 3) != 0)
	{
		char c = *(src++);
		*(dst++) = c;
		if (!c) return r;
	}

	while (1)
	{
		uint32_t v = *(uint32_t*)src;

		if (__builtin_expect((((v) - 0x01010101UL) & ~(v) & 0x80808080UL), 0))
		{
			dst[0] = v & 0xff;
			if ((v & 0xff) == 0)
				return r;
			v = v >> 8;

			dst[1] = v & 0xff;
			if ((v & 0xff) == 0)
				return r;
			v = v >> 8;

			dst[2] = v & 0xff;
			if ((v & 0xff) == 0)
				return r;
			v = v >> 8;

			dst[3] = v & 0xff;
			return r;
		}

		*(uint32_t*)dst = v;
		src += 4;
		dst += 4;
	}
}

int strcmp(const char *s1, const char *s2)
{
	while ((((uint32_t)s1 | (uint32_t)s2) & 3) != 0)
	{
		char c1 = *(s1++);
		char c2 = *(s2++);

		if (c1 != c2)
			return c1 < c2 ? -1 : +1;
		else if (!c1)
			return 0;
	}

	while (1)
	{
		uint32_t v1 = *(uint32_t*)s1;
		uint32_t v2 = *(uint32_t*)s2;

		if (__builtin_expect(v1 != v2, 0))
		{
			char c1, c2;

			c1 = v1 & 0xff, c2 = v2 & 0xff;
			if (c1 != c2) return c1 < c2 ? -1 : +1;
			if (!c1) return 0;
			v1 = v1 >> 8, v2 = v2 >> 8;

			c1 = v1 & 0xff, c2 = v2 & 0xff;
			if (c1 != c2) return c1 < c2 ? -1 : +1;
			if (!c1) return 0;
			v1 = v1 >> 8, v2 = v2 >> 8;

			c1 = v1 & 0xff, c2 = v2 & 0xff;
			if (c1 != c2) return c1 < c2 ? -1 : +1;
			if (!c1) return 0;
			v1 = v1 >> 8, v2 = v2 >> 8;

			c1 = v1 & 0xff, c2 = v2 & 0xff;
			if (c1 != c2) return c1 < c2 ? -1 : +1;
			return 0;
		}

		if (__builtin_expect((((v1) - 0x01010101UL) & ~(v1) & 0x80808080UL), 0))
			return 0;

		s1 += 4;
		s2 += 4;
	}
}
#endif

