/*
Graph constructed with adjacency matrix
G[i][j] in A: i*(i+1)/2+j

*/
#include <stdio.h>
#include <stdlib.h>
#include "graph_matrix.h"

graph *create_graph(int size)
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->arr = (int *)malloc((size * (size + 1) / 2) * sizeof(int));
    for (int i = 0; i < size * (size + 1) / 2; i++)
        g->arr[i] = 0;
    g->size = size;
    return g;
}

graph *insert_vertex(int val, graph *g)
{
    graph *enlarged_graph = create_graph(g->size + 1);
    for (int i = 0; i < g->size * (g->size + 1) / 2; i++)
        enlarged_graph->arr[i] = g->arr[i];
    free(g->arr);
    free(g);
    return enlarged_graph;
}

void insert_edge(graph *g, int n1, int n2)
{
    if (n1 > n2)
        g->arr[n1 * (n1 + 1) / 2 + n2] = 1;
    else if (n1 < n2)
        g->arr[n2 * (n2 + 1) / 2 + n1] = 1;
}

void dfs(graph *g, int vertex)
{
    int *visited = (int *)malloc(g->size * sizeof(int));
    for (int i = 0; i < g->size; i++)
        visited[i] = 0;
    dfs_core(g, vertex, visited);
    printf("\n");
    free(visited);
}

void dfs_core(graph *g, int vertex, int *v)
{
    v[vertex] = 1;
    printf("%d ", vertex);
    for (int i = 0; i < g->size; i++)
    {
        if (i == vertex)
            continue;
        int edge_index;
        edge_index = (i < vertex) ? (vertex * (vertex + 1) / 2 + i) : (i * (i + 1) / 2 + vertex); // compressed index number of graphs' nodes in matrix
        if (v[i] == 0 && g->arr[edge_index] == 1)
            dfs_core(g, i, v);
    }
}

void bfs(graph *g, int vertex)
{
    int *visited = (int *)malloc(g->size * sizeof(int));
    for (int i = 0; i < g->size; i++)
        visited[i] = 0;

    int level = 0;
    int last_curLv = vertex;
    int last_nxtLv; //the last vertex in the next level

    visited[vertex] = 1;
    queue *q = init_queue(q);
    q_push(q, vertex);

    while (q->size != 0)
    {
        int re_val = q_pop(q);

        printf("%d ", re_val);

        for (int i = 0; i < g->size; i++)
        {
            if (i == re_val)
                continue;
            int edge_index;
            edge_index = (i < re_val) ? (re_val * (re_val + 1) / 2 + i) : (i * (i + 1) / 2 + re_val);
            if (visited[i] == 0 && g->arr[edge_index] == 1)
            {
                visited[i] = 1;
                q_push(q, i);
                last_nxtLv = i;
            }
        }

        if (re_val == last_curLv)
        {
            level++;
            last_curLv = last_nxtLv;
        }
    }
    printf("\n");
    free(visited);
}

qnode *create_node(int index)
{
    qnode *newnode = (qnode *)malloc(sizeof(qnode));
    newnode->index = index;
    newnode->next = NULL;
    return newnode;
}

queue *init_queue(queue *q)
{
    q = (queue *)malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void q_push(queue *q, int index)
{
    qnode *newqn = create_node(index);

    if (q->head == NULL)
    {
        q->head = newqn;
        q->tail = newqn;
        q->size++;
        return;
    }
    q->tail->next = newqn;
    q->tail = newqn;
    q->size++;
}

int q_pop(queue *q)
{
    int re = q->head->index;
    qnode *temp = q->head->next;
    free(q->head);
    q->head = temp;
    q->size--;
    return re;
}
