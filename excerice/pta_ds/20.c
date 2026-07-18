#include <stdio.h>
#include <stdlib.h>
#define MAX_V 510

int graph[MAX_V][MAX_V];

void init_graph()
{
    for (int i = 0; i < MAX_V; i++)
    {
        for (int j = 0; j < MAX_V; j++)
        {
            graph[i][j] = -1;
        }
    }
}

void insert(int v1, int v2, int weight)
{
    graph[v1][v2] = graph[v2][v1] = weight;
}


int main()
{
    return 0;
}