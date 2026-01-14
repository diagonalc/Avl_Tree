#include <stdio.h>
#include <stdbool.h>

typedef struct dummy{
    int val;
    int height;
    struct dummy* left;
    struct dummy* right;
} node;

bool search(node *node_ptr, int val){
    if(node_ptr == NULL)
        return 0;
    if(val == node_ptr->val)
        return 1;
    if(val < node_ptr->val)
        return search(node_ptr->left, val);
    else
        return search(node_ptr->right, val);
}

node* insert(node *node_ptr, int val){
    if(node_ptr)
}