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
    return newnode;
}

//         y
//        / \
//       x   black
//      / \ 
//     o   o

node *right_rotate(node *y)
{
    node *yp = y->parent;
    node *x = y->left;
    node *xr = x->right;
    int xcolour = x->colour;
    x->right = y;
    y->left = xr;
    x->colour = y->colour;
    y->colour = xcolour;
    x->parent = yp;
    y->parent = x;
    if (xr)
        xr->parent = y;
    return x;
}

//          y
//         / \
//        o   x
//           / \ 
//          o   o
node *left_rotate(node *y)
{
    node *yp = y->parent;
    node *x = y->right;
    node *xl = x->left;
    int xcolour = x->colour;
    x->left = y;
    y->right = xl;
    x->colour = y->colour;
    y->colour = xcolour;
    x->parent = yp;
    y->parent = x;
    if (xl)
        xl->parent = y;
    return x;
}

/*
-----Lesson learnt: NEVER APPEMPT TO USE WHILE STRUCTURE TO BUILD BST !!!-----

OR ELSE:
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
    node *dummy = cur;
    while (cur != NULL)
    {
        if (val > cur->val)
        {
            dummy = cur;
            cur = cur->right;
        }

        else if (val < cur->val)
        {
            dummy = cur;
            cur = cur->left;
        }

        else if (val == cur->val)
        {
            printf("Data exists\n");
            free(newnode);
            return NULL;
        }
    }
    int lr1 = -1; // left: 0, right: 1
    int lr0 = -1; // lr0: grandparent to parent L/R?  lr1: parent to newnode L/R?
    if (val > dummy->val)
    {
        dummy->right = newnode;
        lr1 = 1;
    }

    else
    {
        dummy->left = newnode;
        lr1 = 0;
    }
    newnode->parent = dummy;
    node *p = newnode->parent;
    node *gp = p->parent;

    if (p->colour == 1)
    {
        lr0 = (gp->left == p) ? 0 : 1;
        node *uncle = (gp->left == p) ? gp->right : gp->left;
        if (uncle->colour == 0 || uncle == NULL)
        {
            // LL
            if (lr1 == 0 && lr0 == 0)
            {
                if (gp->parent)
                {
                    node *ggp = gp->parent;
                    ggp->left = right_rotate(gp);
                    ggp->left->parent = ggp;
                    return r;
                }
                else
                {
                    r = right_rotate(gp);
                    r->parent = NULL;
                    return r;
                }
            }

            // RR
            else if (lr1 == 1 && lr0 == 1)
            {
                if (gp->parent)
                {
                    node *ggp = gp->parent;
                    ggp->right = left_rotate(gp);
                    ggp->right->parent = ggp;
                    return r;
                }
                else
                {
                    r = left_rotate(gp);
                    r->parent = NULL;
                    return r;
                }
            }

            // LR
            else if (lr0 == 0 && lr1 == 1)
            {

            }
            ... I GIVE UP... 
            知錯...
        }
    }
}

*/
