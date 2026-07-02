#include <stdio.h>
#include <stdlib.h>
#define MAX_V 1000

int graph[MAX_V][MAX_V] = {0};

typedef struct queue_node
{
    int val;
    struct qnode *next;
} qnode;

typedef struct queue
{
    struct queue_node *head;
    struct queue_node *tail;
    int size;
} queue;

queue *init_q(queue *q)
{
    q = malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

qnode *create_qnode(int val)
{
    qnode *nn = malloc(sizeof(qnode));
    nn->val = val;
    nn->next = NULL;
    return nn;
}

void enqueue(int val, queue *q)
{
    qnode *nn = create_qnode(val);
    if (q->size == 0)
    {
        q->head = nn;
        q->tail = nn;
        q->size++;
        return;
    }
    q->tail->next = nn;
    q->tail = nn;
    q->size++;
    return;
}

int dequeue(queue *q)
{
    int re = q->head->val;
    qnode *temp = q->head->next;
    free(q->head);
    q->head = temp;
    q->size--;
    return re;
}

int bfs(int n, int v, queue *q)
{
    int visited[MAX_V] = {0};
    enqueue(0, q);
}

void sds(int n)
{
    int ct = 0;
    for (int i = 0; i < n; i++)
    {
    }
}

void insert(int v1, int v2)
{
    graph[v1][v2] = 1;
    graph[v2][v1] = 1;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        int v1, v2;
        scanf(" %d %d", &v1, &v2);
        insert(v1, v2);
    }
    sds(n);
}