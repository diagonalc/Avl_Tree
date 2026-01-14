#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node Node;

// insert:
void insert_head(Node **head, int val);
void insert_tail(Node **head, int val);
void insert_index(Node **head, int value, int index);
void insert_ring_data(Node **head, int val, int target);

// delete:
void delete_data(Node **fhead, int target);
void delete_index(Node **head, int index);

// function:
Node *createnode(int val);
Node *create_link_list(int *arr, int n);
void free_list(Node **head);
void print_list(Node *head);
Node *find_node(Node *head, int target);
int list_len(Node *head);
void inverse_list(Node **head);
void check_ring(Node *head);
void adv_check_ring(Node *head);

Node *createnode(int val)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->data = val;
    newnode->next = NULL;
    return newnode;
}

Node *create_link_list(int *arr, int n)
{
    if (arr == NULL)
    {
        return NULL;
    }
    Node *head = createnode(-1);
    for (int i = 0; i < n; i++)
    {
        insert_tail(&head, arr[i]);
    }
    return head->next;
}

void insert_head(Node **head, int val)
{
    Node *newnode = createnode(val);
    newnode->next = *head;
    *head = newnode;
}

void insert_tail(Node **head, int val)
{
    Node *newnode = createnode(val);
    if (*head == NULL)
    {
        *head = newnode;
        return;
    }
    Node *current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newnode;
}

void insert_index(Node **head, int value, int index)
{
    Node *current = *head;
    if (index == 1)
    {
        insert_head(head, value);
    }

    if (list_len(*head) == 0)
    {
        printf("Linked list does not exist");
        return;
    }
    if (list_len(*head) == index - 1)
    {
        insert_tail(head, value);
    }
    if (list_len(*head) < index - 2)
    {
        printf("Input index is longer than the list");
        return;
    }
    int i;
    for (i = 1; i < index - 1; i++)
    {
        current = current->next;
    }

    Node *newnode = createnode(value);
    Node *temp = current->next;
    current->next = newnode;
    newnode->next = temp;
}

void print_list(Node *head)
{

    Node *current = head;
    if (current == NULL)
    {
        printf("Empty list!");
        return;
    }
    printf("Chain List:");
    while (current != NULL)
    {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

Node *find_node(Node *head, int target)
{
    Node *current = head;
    int count = 1;
    while (current != NULL)
    {
        if (current->data == target)
        {
            return current;
        }
        current = current->next;
        count++;
    }

    // for (int i = 0; i < 100; i++)
    // {
    //     if (arr[i] == 1)
    //     {
    //         printf("Node %d  ", i);
    //     }
    // }
}

void delete_data(Node **fhead, int target)
{
    if (*fhead == NULL)
    {
        printf("Linked list does not exist");
        return;
    }
    Node *current = *fhead;
    if (current->data == target)
    {
        Node *temp = current->next;
        free(current);
        *fhead = temp;
        return;
    }

    while (current->next != NULL)
    {

        if (current->next->data == target)
        {
            Node *temp = current->next;
            current->next = temp->next;
            free(temp);
            return;
        }
        current = current->next;
    }
    printf("target not found");
}

int list_len(Node *head)
{
    int ct = 0;
    if (head == NULL)
    {
        printf("List not found");
        return 0;
    }
    Node *current = head;
    while (current != NULL)
    {
        ct++;
        current = current->next;
    }
    return ct;
}

void inverse_list(Node **head)
{
    int len = list_len(*head);
    // Approach 1
    // Space complexity = O(n)
    /*int arr[len + 5];
    Node *current = head;
    for (int i = 0; i < len; i++)
    {
        arr[i] = current->data;
        current = current->next;
    }

    current = head;
    for (int i = len - 1; i >= 0; i--)
    {
        current->data = arr[i];
        current = current->next;
    }*/

    // Approach 2
    // Space Complexity = O(1)

    Node *prev, *curr, *next;
    prev = NULL;
    curr = *head;
    next = curr->next;
    while (next != NULL)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = next->next;
    }
    curr->next = prev;
    *head = curr;
}

void free_list(Node **head)
{
    Node *current = *head;
    if (*head == NULL)
    {
        printf("Linked list does not exist");
        return;
    }
    while (current->next != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    free(current);
}

void delete_index(Node **head, int index)
{
    Node *current = *head;
    if (index == 1)
    {
        Node *temp = current;
        *head = current->next;
        free(temp);
        return;
    }
    // unfinished
}

void check_ring(Node *head)
{
    Node *curf = head;
    Node *curs = head;
    while (curf->next != NULL)
    {
        curf = curf->next->next;
        curs = curs->next;
        if (curf == curs)
        {

            adv_check_ring(head);
            return;
        }
    }
    printf("Ring does not exist.");
}

void insert_ring_data(Node **head, int val, int target)
{
    Node *current = *head;
    insert_tail(head, val);
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = find_node(*head, target);
}

void adv_check_ring(Node *head)
{
    Node *f, *s;
    s = f = head;
    s = s->next;
    f = f->next->next;
    while (f != s)
    {
        s = s->next;
        f = f->next->next;
    }
    Node *fb, *x;
    x = f;
    fb = head;
    while (fb != x)
    {
        fb = fb->next;
        x = x->next;
    }
    printf("The ring starts at %d", fb->data);
}
