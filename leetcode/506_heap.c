#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct heap
{
    node *arr;
    int size;
    int capacity;
} heap;

typedef struct node
{
    int score;
    char *rank;
} node;

heap *init_heap(int cap)
{
    heap *newheap = (heap *)malloc(sizeof(heap));
    newheap->arr = (node *)malloc(cap * sizeof(node));
    newheap->size = 0;
    newheap->capacity = cap;
    newheap->arr[0].score = 9999999;
    for (int i = 1; i < cap; i++)
        newheap->arr[i].rank = (char *)malloc(20 * sizeof(char));
    return newheap;
}

void *insert(heap *h, int val)
{
    if (h->size == h->capacity)
    {
        printf("Heap is full");
        return;
    }

    int i = (h->size) + 1;
    for (; h->arr[i / 2].score < val; i /= 2)
        h->arr[i] = h->arr[i / 2];
    h->arr[i].score = val;
    h->size++;
}

int *delete(heap *h)
{
    if (h->size == 0)
    {
        printf("Empty heap");
        return;
    }
    int top = h->arr[1].score;
    int last = h->arr[h->size].score;
    h->arr[1].score = last;
    percdown(h, 1);
    h->size--;
    return top;
}

void build_heap(heap *h, int n, int *arr)
{
    if (n > h->capacity)
    {
        printf("Number of inputs exceeds the maximum capacity of the heap");
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf(" %d", &h->arr[i].score);
    }
    for (int i = h->size / 2; i > 0; i--)
    {
        percdown(h, i);
    }
    h->size = n;
}

void build_heap2(heap *h, int n, int *arr)
{
    if (n > h->capacity)
    {
        printf("Number of inputs exceeds the maximum capacity of the heap");
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        insert(h, arr[i]);
    }
    h->size = n;
}

void percdown(heap *h, int p)
{
    int parent = p;
    int child;
    int temp_root = h->arr[1].score;
    for (; parent * 2 <= h->size; parent = child)
    {
        child = parent * 2;
        if ((child != h->size) && (h->arr[child].score < h->arr[child + 1].score))
            child++;
        if (temp_root > h->arr[child].score)
            break;
        else
            h->arr[parent].score = h->arr[child].score;
    }
    h->arr[parent].score = temp_root;
}

void assign_rank(heap *h, int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (i == 1)
            strcpy(h->arr[i].rank, "Gold Medal");

        else if (i == 2)
            strcpy(h->arr[i].rank, "Silver Medal");

        else if (i == 3)
            strcpy(h->arr[i].rank, "Bronze Medal");

        else
        {
            char r = i - '0';
            strcpy(h->arr[i].rank, r);
        }
    }
}

void print_rank(heap *h, int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("%s\n", h->arr[i].rank);
    }
}

int main()
{
    int arr[] = {5, 4, 3, 2, 1};
    heap *h = init_heap(5);
    build_heap(h, 5, arr);
    assign_rank(h, 5);
    print_rank(h, 5);

    return 0;
}