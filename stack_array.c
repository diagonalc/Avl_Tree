#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    int *arr;
    int size;
    int cap;
} stack;

// functions:
stack *init_stack(int cap);
void push(stack *s, int val);
int pop(stack *s);
void free_stack(stack *s);
int null_check(stack *s);
void print_stack(stack *s);

stack *init_stack(int cap)
{
    stack *newstack = (stack *)malloc(sizeof(stack));
    newstack->arr = (int *)malloc(cap * sizeof(int));
    newstack->cap = cap;
    newstack->size = 0;
    return newstack;
}

void push(stack *s, int val)
{
    if (null_check(s) != 0)
        return;
    if (s->size == s->cap)
    {
        printf("Stack is full\n");
        return;
    }
    s->arr[s->size] = val;
    s->size++;
}

int pop(stack *s)
{
    if (null_check(s) != 0)
        return -1;
    int temp = s->arr[--s->size];
    return temp;
}

void free_stack(stack *s)
{
    if (null_check(s) != 0)
        return;
    for (int i = 0; i < s->size; i++)
        free(&s->arr[i]);
    free(s);
}

int null_check(stack *s)
{
    if (s == NULL)
    {
        printf("Stack does not exist\n");
        return 1;
    }
    return 0;
}

void print_stack(stack *s)
{
    if (null_check(s) != 0)
        return;
    for (int i = 0; i < s->size; i++)
        printf("%d ", s->arr[i]);
}

int main()
{
    stack *s = init_stack(10);
    push(s, 2);
    push(s, 5);
    pop(s);
    push(s, 7);
    print_stack(s);

    return 0;
}