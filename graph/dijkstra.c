/*
dijkstra algorithm optimized with minimum heap
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_VERTEX 10

/*
pseudocode:
void Dijkstra( Vertex s )
{
    while (1){
        V = 未收录顶点中dist最小者;
        if ( 这样的V不存在 )
            break;
        collected[V] = true;
        for ( V 的每个邻接点 W ){
            if ( collected[W] == false ){
                if ( dist[V]+E<V,W> < dist[W] ) {
                    dist[W] = dist[V] + E<V,W> ;
                    path[W] = V;
                }
            }
        }
    }
}
*/

typedef struct minheap_node hnode;
typedef struct minheap heap;
struct minheap_node
{
    int dist;
    int v_index;
};
struct minheap
{
    struct minheap_node *arr;
    int size;
    int capacity;
};

int graph[MAX_VERTEX][MAX_VERTEX];

void init_graph()
{
    for (int i = 0; i < MAX_VERTEX; i++)
        for (int j = 0; j < MAX_VERTEX; j++)
            graph[i][j] = INT_MAX;
}
void build_graph()
{
    int edge_num;
    scanf("%d", &edge_num);
    printf("Input format: (from) (to) (weight)\n");
    for (int i = 0; i < edge_num; i++)
    {
        int f, t, w;
        scanf("%d %d %d", &f, &t, &w);
        graph[f][t] = w;
    }
}

heap *init_heap(int cap)
{
    heap *h = (heap *)malloc(sizeof(heap));
    h->capacity = cap;
    h->size = 0;
    h->arr = (hnode *)malloc((cap + 1) * sizeof(hnode)); // the heap begins to store data from index 1
    h->arr[0].dist = -INT_MAX;
    h->arr[0].v_index = 0;
    return h;
}

void h_insert(heap *h, int w, int v_index)
{
    if (h->size == h->capacity)
        return;

    int i = ++h->size; // the heap begins to store data from index 1
    while (i > 1 && h->arr[i / 2].dist > w)
    {
        h->arr[i] = h->arr[i / 2];
        i /= 2;
    }
    h->arr[i].v_index = v_index;
    h->arr[i].dist = w;
}

hnode h_pop(heap *h)
{
    if (h->size == 0)
    {
        hnode empty = {0, -1};
        return empty;
    }
    hnode top = h->arr[1];
    int parent, child;
    hnode last = h->arr[h->size--]; // h->size--; already
    for (parent = 1; parent * 2 <= h->size; parent = child)
    {
        child = parent * 2;
        if ((child != h->size) && (h->arr[child].dist > h->arr[child + 1].dist))
            child++;
        if (h->arr[child].dist >= last.dist)
            break;
        h->arr[parent] = h->arr[child];
    }
    h->arr[parent] = last;
    return top;
}

void h_free(heap *h)
{
    free(h->arr);
    free(h);
}

void dijkstra(int st, int *dist, int *path)
{
    // dist stores the distance from the start to vi, graph stores the weight of a single edge

    heap *h = init_heap(10);
    int collected[MAX_VERTEX] = {0};

    for (int i = 0; i < MAX_VERTEX; i++)
    {
        dist[i] = INT_MAX;
        path[i] = -1;
    }
    dist[st] = 0;
    h_insert(h, 0, st);

    for (int i = 0; i < MAX_VERTEX; i++)
    {
        if (graph[st][i])
        {
            path[st] = st;
            h_insert(h, graph[st][i], i);
        }
    }

    while (1)
    {
        hnode v = h_pop(h);
        int vi = v.v_index;
        int vd = v.dist;
        if (vi == -1)
            break;
        if (vd > dist[vi]) // skip the outdated node, if dist[vi] is shorter than  the distance stores in hnode, there should be a updated hnode inside the heap already
            continue;
        
        collected[vi] = 1;
        for (int i = 0; i < MAX_VERTEX; i++)
        {
            if (graph[vi][i] != INT_MAX && collected[i] == 0 && i != st) // if no edge exists between a and b, graph[a][b] equals to INT_MAX
            // skip when i == st
            {
                int new_dist = dist[vi] + graph[vi][i];
                if (new_dist < dist[i])
                {
                    dist[i] = new_dist;
                    path[i] = vi;
                    h_insert(h, dist[i], i);
                }
            }
        }
    }
    h_free(h);
}



int main()
{
    init_graph();
    int dist[MAX_VERTEX];
    int path[MAX_VERTEX];
    int st = 0;
    graph[0][1] = 10;
    graph[0][3] = 5;
    graph[1][2] = 1;
    graph[1][3] = 2;
    graph[2][4] = 4;
    graph[3][1] = 3;
    graph[3][2] = 9;
    graph[3][4] = 2;
    graph[4][2] = 6;
    graph[4][0] = 7;
    dijkstra(st, dist, path);
    printf("minimum distance from %d:\n", st);
    for (int i = 0; i < 6; i++)
    {
        printf("to %d: ", i);
        if (dist[i] == INT_MAX)
            printf("INF\n");
        else
            printf("%d\n", dist[i]);
    }

    return 0;
}