#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Max_Heap
{
    int *arr;
    int size;
    int capacity;
} heap;  

// functions:
heap *init_heap(int maxsize);
void insert(heap *h, int val);
int delete(heap *h);
void build_heap(heap *h);
void build_heap_opt(heap *h, int *arr, int a_size);
void maxheapify(heap *h, int p);
void percdown(heap *h, int p);
void print_heap(heap *h);
void free_heap(heap *h);

heap *init_heap(int maxsize)
{
    heap *h = (heap *)malloc(sizeof(heap));
    h->arr = (int *)malloc((maxsize + 1) * sizeof(int));
    h->size = 0;
    h->capacity = maxsize;
    h->arr[0] = 99999999; // guard
    return h;
}

void insert(heap *h, int val)
{
    if (h->size == h->capacity)
    {
        printf("Heap is full\n");
        return;
    }

    int i = ++(h->size);
    for (; h->arr[i / 2] < val; i /= 2) // filtering the nodes
        h->arr[i] = h->arr[i / 2];
    h->arr[i] = val;
}

int delete(heap *h)
{
    if (h->size == 0)
    {
        printf("Empty heap\n");
        return 0;
    }

    int max = h->arr[1];
    int last = h->arr[h->size];
    h->arr[1] = last;
    h->size--;
    percdown(h, 1);
    return max;
}

// O(NlogN)
void build_heap(heap *h)
{
    int n;
    scanf("%d", &n);
    if (n > h->capacity)
    {
        printf("Number of inputs exceeds the maximum capacity of the heap");
        return;
    }
    for (int i = 1; i <= n; i++)
        scanf(" %d", &h->arr[i]);
    h->size = n;
    for (int i = h->size; i > 0; i--)
        percdown(h, i);
}

// O(N) method
void build_heap_opt(heap *h, int *arr, int a_size)
{
    h->size = a_size;
    for (int i = 0; i < a_size; i++)
        h->arr[i + 1] = arr[i];
    for (int i = h->size / 2; i > 0; i--)
        maxheapify(h, i);
}

void maxheapify(heap *h, int p)
{
    int l = p * 2, r = p * 2 + 1, largest = p;
    if (l <= h->size && h->arr[l] > h->arr[largest])
        largest = l;
    if (r <= h->size && h->arr[r] > h->arr[largest])
        largest = r;
    if (largest != p)
    {
        int temp = h->arr[p];
        h->arr[p] = h->arr[largest];
        h->arr[largest] = temp;
        maxheapify(h, largest);
    }
}

void percdown(heap *h, int p)
{
    int parent, child, temp_root;
    parent = p;
    temp_root = h->arr[p];
    for (; parent * 2 <= h->size; parent = child)
    {
        child = parent * 2;
        if ((child != h->size) && h->arr[child] < h->arr[child + 1])
            child++;
        if (temp_root >= h->arr[child])
            break;
        else
            h->arr[parent] = h->arr[child];
    }
    h->arr[parent] = temp_root;
}

void print_heap(heap *h)
{
    int p = 1;
    for (int i = 1; i <= h->size; i++)
    {
        if (i == pow(2, p) - 1)
        {
            printf("%d\n", h->arr[i]);
            p++;
        }

        else
            printf("%d ", h->arr[i]);
    }
    printf("\n");
}

void free_heap(heap *h)
{
    free(h->arr);
    free(h);
}

int main()
{
    heap *h = init_heap(10);
    build_heap(h);
    print_heap(h);
    delete(h);
    insert(h, 20);
    print_heap(h);
    return 0;
}