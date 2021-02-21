#include <stdio.h>

int main()
{
    printf("Bonjour main() !\n");
    int sum=0;
    for(int i=0; i<7; ++i) sum += i;
    printf("Total: %d\n", sum);
}
