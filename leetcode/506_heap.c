/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int score;
    char *rank;
} node;

typedef struct heap
{
    node *arr;
    int size;
    int capacity;
} heap;

// 1. Forward declaration so 'delete' and 'build_heap' can find it
void percdown(heap *h, int p);

heap *init_heap(int cap)
{
    heap *newheap = (heap *)malloc(sizeof(heap));
    newheap->arr = (node *)malloc((cap + 1) * sizeof(node));
    newheap->size = 0;
    newheap->capacity = cap;
    newheap->arr[0].score = 9999999;
    for (int i = 1; i <= cap; i++)
        newheap->arr[i].rank = (char *)malloc(20 * sizeof(char));
    return newheap;
}

void insert(heap *h, int val)
{
    if (h->size == h->capacity)
    {
        printf("Heap is full");
        return;
    }

    int i = (h->size) + 1;
    for (; h->arr[i / 2].score < val; i /= 2)
        h->arr[i].score = h->arr[i / 2].score;
    h->arr[i].score = val;
    h->size++;
}

int delete(heap *h)
{
    if (h->size == 0)
    {
        printf("Empty heap");
        return -1; // 2. Fixed to return an int
    }
    int top = h->arr[1].score;
    int last = h->arr[h->size].score;
    h->arr[1].score = last;
    h->size--;
    percdown(h, 1);

    return top;
}

void build_heap(heap *h, int n, int *arr)
{
    if (n > h->capacity)
    {
        printf("Number of inputs exceeds the maximum capacity of the heap");
        return;
    }
    h->size = n;
    for (int i = 1; i <= n; i++)
    {
        h->arr[i].score = arr[i - 1];
    }
    for (int i = h->size / 2; i > 0; i--)
    {
        percdown(h, i);
    }
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
    // 3. Fixed to use 'p' instead of '1' so it percolates the correct node
    int temp_root = h->arr[p].score;
    for (; parent * 2 <= h->size; parent = child)
    {
        child = parent * 2;
        if ((child != h->size) && (h->arr[child].score < h->arr[child + 1].score))
            child++;

        // 4. Added '=' to prevent infinite loops on duplicates
        if (temp_root >= h->arr[child].score)
            break;
        else
            h->arr[parent].score = h->arr[child].score;
    }
    h->arr[parent].score = temp_root;
}

// (I kept assign_rank here per your request, though we bypass it below)
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
            sprintf(h->arr[i].rank, "%d", i);
        }
    }
}

// 5. Finished LeetCode function
char **findRelativeRanks(int *score, int scoreSize, int *returnSize)
{
    *returnSize = scoreSize;

    // Allocate the return array of strings
    char **result = (char **)malloc(scoreSize * sizeof(char *));

    heap *h = init_heap(scoreSize);
    build_heap(h, scoreSize, score);

    // Repeatedly delete the top of the heap to get strictly descending scores
    for (int i = 1; i <= scoreSize; i++)
    {
        int max_score = delete(h);

        // Find where this max_score was located in the original array
        int original_idx = 0;
        for (int j = 0; j < scoreSize; j++)
        {
            if (score[j] == max_score)
            {
                original_idx = j;
                break;
            }
        }

        // Allocate memory for the specific string and assign the rank directly to the original index
        result[original_idx] = (char *)malloc(20 * sizeof(char));

        if (i == 1)
            strcpy(result[original_idx], "Gold Medal");
        else if (i == 2)
            strcpy(result[original_idx], "Silver Medal");
        else if (i == 3)
            strcpy(result[original_idx], "Bronze Medal");
        else
            sprintf(result[original_idx], "%d", i);
    }

    // Clean up heap memory to prevent LeetCode memory leaks
    for (int i = 1; i <= h->capacity; i++)
    {
        free(h->arr[i].rank);
    }
    free(h->arr);
    free(h);

    return result;
}