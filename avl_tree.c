#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
    int height;
} node;

// 1. insert
node *insert(node *rnode, int val);

// 2. delete
node *delete_leaf(node *n, int val); // unfin
// 3. search
node *search(node *n, int val);

// 4. functions
node *cnewnode(int val);
node *right_rotate(node *y);
node *left_rotate(node *y);
void update_tree_height(node *root);
void balance_check(node *root);

// 5. miscellaneous
int max(int a, int b);
int height(node *root);
int balance_fac(node *n);

int max(int a, int b)
{
    return a > b ? a : b;
}

int height(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

node *cnewnode(int val)
{
    node *newnode = (node *)malloc((sizeof(node)));
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1;
    return newnode;
}

int balance_fac(node *n)
{
    if (n == NULL)
        return -999;
    return height(n->left) - height(n->right);
}

//         y
//        / \
//       x   o
//      / \ 
//     o   o
node *right_rotate(node *y)
{
    node *x = y->left;
    node *xr = x->right;
    x->right = y;
    y->left = xr;
    x->height = height(x);
    y->height = height(y);
    return x;
}

//          y
//         / \
//        o   x
//           / \ 
//          o   o
node *left_rotate(node *y)
{
    node *x = y->right;
    node *xl = x->left;
    x->left = y;
    y->right = xl;
    x->height = height(x);
    y->height = height(y);
    return x;
}

node *insert(node *rnode, int val)
{

    if (rnode == NULL)
    {
        return cnewnode(val);
    }
    if (val < rnode->val)
    {
        rnode->left = insert(rnode->left, val);
    }
    else if (val > rnode->val)
    {
        rnode->right = insert(rnode->right, val);
    }
    else
    {
        printf("node existed!");
        return rnode;
    }

    // update tree height for each sub. tree

    rnode->height = height(rnode);

    int bfroot = balance_fac(rnode);
    int bfl = balance_fac(rnode->left);
    int bfr = balance_fac(rnode->right);

    // LL
    if (bfroot == 2 && bfl == 1)
    {
        return right_rotate(rnode);
    }
    // RR
    else if (bfroot == -2 && bfr == -1)
    {
        return left_rotate(rnode);
    }
    // LR
    else if (bfroot == 2 && bfl == -1)
    {
        rnode->left = left_rotate(rnode->left);
        return right_rotate(rnode);
    }
    // RL
    else if (bfroot == -2 && bfr == 1)
    {
        rnode->right = right_rotate(rnode->right);
        return left_rotate(rnode);
    }

    return rnode;
}

// unfin
node *delete_leaf(node *n, int val)
{
    node *cur = n;
    if (search(n, val) == NULL)
    {
        printf("Node does not exist");
        return NULL;
    }
    else if (val == cur->val)
    {
        return n;
    }
    while (cur != NULL)
    {
        if (val == cur->left->val)
        {
            node *temp = cur->left;
            cur->left = NULL;
            free(temp);
            update_tree_height(n);
            return n;
        }
        else if (val == cur->right->val)
        {
            node *temp = cur->right;
            cur->right = NULL;
            free(temp);
            update_tree_height(n);
            return n;
        }
        if (val < cur->val)
        {
            cur = cur->left;
        }
        else if (val > cur->val)
        {
            cur = cur->right;
        }
    }
}

void update_tree_height(node *root)
{
    if (root == NULL)
    {
        return;
    }
    root->height = height(root);
    update_tree_height(root->left);
    update_tree_height(root->right);
    return;
}

void balance_check(node *root)
{
}

node *search(node *n, int val)
{
    if (n == NULL)
    {
        printf("Node does not exist");
        return NULL;
    }
    if (val < n->val)
    {
        search(n->left, val);
    }
    else if (val > n->val)
    {
        search(n->right, val);
    }
    else if (val == n->val)
    {
        return n;
    }
}

int main()
{
    node *root = cnewnode(10);

    root = insert(root, 9);
    root = insert(root, 8);
    node *t = search(root, 8);
    delete_leaf(root, 8);
    printf("%d", root->left->val);
    return 0;
}