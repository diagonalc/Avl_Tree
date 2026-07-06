#include <stdio.h>
#include <string.h>

struct edge
{
    int x;
    int y;
};

int main()
{
    struct edge e[10] = {0,0};
   
    printf("%d %d", e[2].x, e[2].y);
}