    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #define MAX_V 10000

    int graph[MAX_V][MAX_V] = {0};

    typedef struct queue_node
    {
        int val;
        struct queue_node *next;
    } qnode;

    typedef struct queue
    {
        struct queue_node *head;
        struct queue_node *tail;
        int size;
    } queue;

    queue *init_q()
    {
        queue *q = malloc(sizeof(queue));
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

    bool is_empty(queue *q)
    {
        return (q->size == 0) ? true : false;
    }

    int bfs(int n, int v, queue *q)
    {
        int visited[MAX_V] = {0};
        int count = 0;
        int level = 0;
        enqueue(v, q);
        while ((!is_empty(q)) && level < 6)
        {
            int size = q->size; // q->size snapshot: level by level
            for (int j = 0; j < size; j++)
            {
                int cur = dequeue(q);
                for (int i = 1; i <= n; i++)
                {
                    if (i == cur)
                        continue;
                    if ((graph[i][cur] || graph[cur][i]) && visited[i] == 0)
                    {
                        enqueue(i, q);
                        visited[i] = 1;
                        count++;
                    }
                }
            }
            level++;
        }

        return count;
    }

    void free_q(queue *q)
    {
        while (!is_empty(q))
            dequeue(q);
        free(q);
    }

    void sds(int n)
    {

        for (int i = 1; i < n; i++)
        {
            queue *q = init_q();
            int ct = bfs(n, i, q);
            // printf("%d\n", ct);
            free_q(q);
            printf("%d: %.2lf%%\n", i, ((double)ct / n) * 100);
        }
        queue *q = init_q();
        int ct = bfs(n, n, q);
        free_q(q);
        printf("%d: %.2lf%%", n, ((double)ct / n) * 100);
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
        for (int i = 0; i < m; i++)
        {
            int v1, v2;
            scanf(" %d %d", &v1, &v2);
            insert(v1, v2);
        }
        sds(n);

        // queue *q = init_q();
        // enqueue(0, q);
        // enqueue(1, q);
        // enqueue(2, q);
        // enqueue(3, q);
        // int re1 = dequeue(q);
        // printf("%d ", re1);
        // dequeue(q);
        // printf("%d", dequeue(q));
        return 0;
    }