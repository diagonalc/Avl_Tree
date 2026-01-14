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
node *delete_node(node *n, int val); 
// 3. search
node *search(node *n, int val);

// 4. functions
node *cnewnode(int val);
node *right_rotate(node *y);
node *left_rotate(node *y);
void update_tree_height(node *root);
void balance_check(node *root);
void print_tree(node *r);

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
        return 0;
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


node *delete_node(node *n, int val)
{

    if (search(n, val) == NULL)
    {
        printf("Node does not exist");
        return NULL;
    }

    if (val < n->val)
    {
        n->left = delete_node(n->left, val);
    }
    else if (val > n->val)
    {
        n->right = delete_node(n->right, val);
    }

    else if (val == n->val)
    {
        return NULL;
    }

    n->height = height(n);

    int bfroot = balance_fac(n);
    int bfl = balance_fac(n->left);
    int bfr = balance_fac(n->right);

    // LL
    if (bfroot == 2 && bfl == 1)
    {
        return right_rotate(n);
    }
    // RR
    else if (bfroot == -2 && bfr == -1)
    {
        return left_rotate(n);
    }
    // LR
    else if (bfroot == 2 && bfl == -1)
    {
        n->left = left_rotate(n->left);
        return right_rotate(n);
    }
    // RL
    else if (bfroot == -2 && bfr == 1)
    {
        n->right = right_rotate(n->right);
        return left_rotate(n);
    }

    return n;
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

void print_tree(node* r){

}

int main()
{
    node *root = cnewnode(10);

    root = insert(root, 9);
    root = insert(root, 11);
    root = insert(root, 8);
    root = delete_node(root, 11);
    printf("%d", root->left->val);
    return 0;
}