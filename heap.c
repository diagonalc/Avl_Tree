#include <stdio.h>
#include <stdlib.h>

typedef struct Max_Heap{
    int *arr;
    int size;
    int capacity;
}heap;

heap *create_heap(int maxsize){
    heap *h = (heap *)malloc(sizeof(heap));
    h->arr = (heap *)malloc((maxsize + 1) * sizeof(int));
    h->size = 0;
    h->capacity = maxsize;
    h->arr[0] = 0;
    return h;
}

void insert(heap* h, int val){
    if(h->size == h->capacity){
        printf("Heap is full\n");
        return;
    }

    int i = ++(h->size);
    for (; h->arr[i / 2] < val;i/=2) //filtering the nodes
        h->arr[i] = h->arr[i / 2];
    h->arr[i] = val;
}