#include <stdio.h>
#include <stdlib.h>

typedef struct stack_node
{
    int val;
    struct stack_node *next;
} stack;

// functions
stack *create_node(int val);
int null_check(stack *s);
stack *push(stack *s, int val);
int pop(stack *h);
void free_stack(stack *h);
void print_stack(stack *h);

stack *create_node(int val)
{
    stack *newnode = (stack *)malloc(sizeof(stack));
    newnode->val = val;
    return newnode;
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

stack *push(stack *h, int val)
{
    if (h == NULL)
    {
        stack *newnode = create_node(val);
        return newnode;
    }
    stack *newnode = create_node(val);
    stack *cur = h;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = newnode;
    return h;
}

int pop(stack *h)
{
    if (null_check(h) != 0)
        return -1;
    stack *cur = h;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    int temp = cur->val;
    free(cur);
    return temp;
}

void free_stack(stack *h)
{
    if (null_check(h) != 0)
        return;
    stack *cur = h;
    while (cur->next != NULL)
    {
        stack *temp = cur->next;
        free(cur);
        cur = temp;
    }
    free(cur);
}

void print_stack(stack *h)
{
    if (null_check(h) != 0)
        return;
    stack *cur = h;
    while (cur != NULL)
    {
        printf("%d ", cur->val);
        cur = cur->next;
    }
}

int main()
{
    stack *h = create_node(1);
    push(h, 2);
    push(h, 5);
    pop(h);
    push(h, 7);
    print_stack(h);

    return 0;
}
