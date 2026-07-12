#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int a = 0;
    int b;
    if ((b = a + 1) > 3)
    {
        printf("impossible");
    }
    printf("%d", b);
}