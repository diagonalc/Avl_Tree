#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX_V 100

typedef struct adjacent_node
{
    int ver_index;
    struct adjacent_node *next;
} adjn;

typedef struct node
{
    int x;
    int y;
    adjn *head;
} node;

typedef struct route
{
    int x;
    int y;
} route;

struct node graph[MAX_V];

void init_graph()
{
    for (int i = 0; i < MAX_V; i++)
    {
        graph[i].x = 0;
        graph[i].y = 0;
        graph[i].head = NULL;
    }
}

adjn *create_adjn(int vertex_index)
{
    adjn *nn = malloc(sizeof(adjn));
    nn->ver_index = vertex_index;
    nn->next = NULL;
    return nn;
}

void insert(int v, int vi)
{
    adjn *nn = create_adjn(vi);
    if (graph[v].head == NULL)
        graph[v].head = nn;
    else
    {
        adjn *cur = graph[v].head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = nn;
    }

    adjn *nn2 = create_adjn(v);
    if (graph[vi].head == NULL)
        graph[vi].head = nn2;
    else
    {
        adjn *cur = graph[vi].head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = nn2;
    }
}

bool prox(node a, node b, double d)
{
    if ((pow(a.x - b.x, 2) + pow(a.y - b.y, 2)) <= pow(d, 2))
        return true;
    return false;
}

void build_graph(int n, int d)
{
    for (int i = 0; i < n; i++)
        scanf(" %d %d", &graph[i].x, &graph[i].y);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (i == j)
                continue;
            if (prox(graph[i], graph[j], d))
            {
                insert(i, j);
            }
        }
    }
}

route r[10000] = {0, 0};
int count = 0;
bool dfs(int v, int visited[], int d)
{
    r[v].x = graph[v].x;
    r[v].y = graph[v].y;
    count++;
    visited[v] = 1;
    if (pow(50 - graph[v].x, 2) <= pow(d, 2) || pow(50 - graph[v].y, 2) <= pow(d, 2))
        return true;
    adjn *cur = graph[v].head;
    while (cur)
    {
        if (visited[cur->ver_index] == 0)
            if (dfs(cur->ver_index, visited, d))
                return true;
        cur = cur->next;
    }
    r[v].x = 0;
    r[v].y = 0;
    count--;
    return false;
}

int main()
{
    int n, d;
    scanf("%d %d", &n, &d);
    init_graph();
    build_graph(n, d);
    int visited[MAX_V] = {0};
    node st_pt = {0, 0, NULL};
    if (d + 7.5 >= 50)
    {
        printf("Yes");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        if (prox(st_pt, graph[i], d + 7.5))
        {
            if (dfs(i, visited, d))
            {
                printf("%d\n", count);
                for (int j = count; j >= 0; j--)
                {
                    printf("%d %d\n", r[j].x, r[j].y);
                }
                    return 0;
            }
        }
    }
    printf("No");
    return 0;
}