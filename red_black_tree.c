#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
    struct node *parent;
    int colour;
} node;

node *createnode(int val)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    newnode->colour = 1; // Red: 1, Black: 0
}

node *insert(int val, node *r)
{
    node *newnode = createnode(val);
    if (r == NULL)
    {
        newnode->colour = 0;
        newnode->val = val;
        return newnode;
    }
    node *cur = r;
    while (cur != NULL)
    {
        if (val > cur->val)
            cur = cur->right;
        else if (val < cur->val)
            cur = cur->left;
        else if (val == cur->val)
        {
            printf("Data exists\n");
            free(newnode);
            return NULL;
        }
    }
    int lr1 = -1; // left: 0, right: 1
    int lr0 = -1; // lr0: grandparent to parent L/R?  lr1: parent to newnode L/R?
    if (val > cur->parent->val)
    {
        cur->parent->right = newnode;
        lr1 = 1;
    }

    else
    {
        cur->parent->left = newnode;
        lr1 = 0;
    }
    newnode->parent = cur->parent;
    node *p = newnode->parent;
    node *gp = p->parent;

    if (newnode->parent->colour == 1)
    {
        lr0 = (gp->left == p) ? 0 : 1;
        // if (gp->)
        // {
        // }
    }
}
