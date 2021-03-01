#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("sizeof(char)      %d\n", sizeof(char));
    printf("sizeof(short)     %d\n", sizeof(short));
    printf("sizeof(int)       %d\n", sizeof(int));
    printf("sizeof(long)      %d\n", sizeof(long));
    printf("sizeof(long long) %d\n", sizeof(long long));

    int l;
    l = printf("x: %x", -123);
    for(int i=0; i<18-l; ++i) printf(" ");
    printf("printf returned %d\n", l);
    l = printf("d: %d", -123);
    for(int i=0; i<18-l; ++i) printf(" ");
    printf("printf returned %d\n", l);
    l = printf("u: %u", -123);
    for(int i=0; i<18-l; ++i) printf(" ");
    printf("printf returned %d\n", l);
    l = printf("s: %s", "123");
    for(int i=0; i<18-l; ++i) printf(" ");
    printf("printf returned %d\n", l);
    l = printf("c: %c", '1');
    for(int i=0; i<18-l; ++i) printf(" ");
    printf("printf returned %d\n", l);
    return 0;
}
