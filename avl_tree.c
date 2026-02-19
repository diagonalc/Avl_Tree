#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
    int height;
} node;

typedef struct qnode
{
    struct Node *ad;
    struct qnode *next;
} qnode;

typedef struct queue
{
    qnode *head;
    qnode *tail;
    int size;
} queue;

// hau wing shing
typedef struct dummy
{
    node *val;
    struct dummy *next;
} ll_node;
// hau wing shing end

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
void print_tree2(node *r);

// 5. miscellaneous
int max(int a, int b);
int height(node *root);
int balance_fac(node *n);
node *successor(node *n);

// 6. queue
qnode *cqnode(node *ad);
void queue_init(queue *q);
void q_push(queue *q, node *ad);
void q_pop(queue *q);

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

    //BST insert
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
        if (n->left == NULL || n->right == NULL)
        {
            node *temp = (n->left) ? n->left : n->right;
            free(n);
            return temp;
        }
        else
        {
            node *sus = successor(n);
            n->val = sus->val;
            n->right = delete_node(n->right, sus->val);
        }
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

node *successor(node *n)
{

    node *cur = n->right;
    while (cur->left != NULL)
    {
        cur = cur->left;
    }
    return cur;
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

node *search(node *n, int val)
{
    if (n == NULL)
    {
        printf("Node does not exist");
        return NULL;
    }
    if (val < n->val)
    {
        return search(n->left, val);
    }
    else if (val > n->val)
    {
        return search(n->right, val);
    }
    else
    {
        return n;
    }
}

void print_tree(node *r)
{
    queue *q = (queue *)malloc(sizeof(queue));
    queue_init(q);
    if (r == NULL)
    {
        printf("Empty Tree");
        return;
    }
    q_push(q, r);
    int layer_n = 1;
    int next_ln = 0;
    while (q->head != NULL)
    {
        printf("%d ", q->head->ad->val);
        if (q->head->ad->left)
        {
            q_push(q, q->head->ad->left);
            next_ln++;
        }

        if (q->head->ad->right)
        {
            q_push(q, q->head->ad->right);
            next_ln++;
        }

        q_pop(q);
        layer_n--;
        if (layer_n == 0)
        {
            printf("\n");
            layer_n = next_ln;
            next_ln = 0;
        }
    }
}

// hau wing shing
void print_tree2(node *r)
{
    ll_node *current = malloc(sizeof(ll_node));
    *current = (ll_node){r, NULL};
    ll_node *end = current;
    while (current != NULL)
    {
        if (current->val != NULL)
        {
            printf("%d\n", current->val->val);
            end->next = malloc(sizeof(ll_node));
            *end->next = (ll_node){current->val->left, NULL};
            end->next->next = malloc(sizeof(ll_node));
            *end->next->next = (ll_node){current->val->right, NULL};
            end = end->next->next;
        }
        ll_node *old = current;
        current = current->next;
        free(old);
    }
}
// hau wing shing end

qnode *cqnode(node *ad)
{
    qnode *newnode = (qnode *)malloc(sizeof(qnode));
    newnode->ad = ad;
    newnode->next = NULL;
    return newnode;
}

void queue_init(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void q_push(queue *q, node *ad)
{
    qnode *newnode = cqnode(ad);
    if (newnode == NULL)
    {
        printf("malloc error");
        return;
    }
    if (q->head == NULL)
    {
        q->head = newnode;
        q->tail = newnode;
        q->size++;
        return;
    }
    else
    {
        qnode *tail = q->tail;
        tail->next = newnode;
        q->tail = newnode;
        q->size++;
    }
    return;
}

void q_pop(queue *q)
{
    if (q->head == NULL)
    {
        printf("empty queue");
        return;
    }

    qnode *temp = q->head->next;
    free(q->head);
    q->head = temp;
    return;
}

int main()
{
    node *root = cnewnode(10);

    root = insert(root, 9);
    root = insert(root, 11);
    root = insert(root, 8);
    root = delete_node(root, 10);
    print_tree(root);

    return 0;
}