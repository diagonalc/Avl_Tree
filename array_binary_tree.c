#include <stdio.h>
#include <stdlib.h>

#define null -1
#define max_tree 10

/*Sample input:
5
A 1 2
B 3 4
C - -
D - -
E - -
5
B 2 4
C - -
E - -
A 1 0
D - -

check if they are isomorphic
(yes for this sample)
*/

typedef struct Tree_node
{
    char data;
    int left;
    int right;
} node;

// functions:
int build_tree(node t[]);
void print_tree(node t[], int r);
int is_isomorphic(node t1[], node t2[], int r1, int r2);



int build_tree(node t[])
{
    int n = 0;
    scanf("%d", &n);
    if (n)
    {
        int check[max_tree] = {0};
        for (int i = 0; i < n; i++)
        {
            char tl, tr;
            scanf(" %c %c %c", &t[i].data, &tl, &tr);
            if (tl != '-')
            {
                t[i].left = tl - '0';
                check[t[i].left] = 1;
            }
            else
                t[i].left = null;
            if (tr != '-')
            {
                t[i].right = tr - '0';
                check[t[i].right] = 1;
            }
            else
                t[i].right = null;
        }
        for (int i = 0; i < n; i++)
        {
            if (!check[i])
                return i;
        }
    }
    return null;
}

void print_tree(node t[], int r)
{
    if (r == null)
        return;
    printf("%c", t[r].data);
    print_tree(t, t[r].left);
    print_tree(t, t[r].right);
}

int is_isomorphic(node t1[], node t2[], int r1, int r2)
{
    if (r1 == null && r2 == null)
        return 1;
    if (r1 == null && r2 != null || r1 != null && r2 == null)
        return 0;
    if (t1[r1].data != t2[r2].data)
        return 0;
    if (t1[r1].left == null && t2[r2].left == null)
        return is_isomorphic(t1, t2, t1[r1].right, t2[r2].right);
    if ((t1[r1].left != null && t2[r2].left != null) && t1[t1[r1].left].data == t2[t2[r2].left].data)
        return (is_isomorphic(t1, t2, t1[r1].left, t2[r2].left) && is_isomorphic(t1, t2, t1[r1].right, t2[r2].right));
    else
        return (is_isomorphic(t1, t2, t1[r1].left, t2[r2].right) && is_isomorphic(t1, t2, t1[r1].right, t2[r2].left));
}

int main()
{
    node t1[max_tree], t2[max_tree];
    int r1, r2;
    r1 = build_tree(t1);
    r2 = build_tree(t2);
    printf("%c", (is_isomorphic(t1, t2, r1, r2)) ? 'Y' : 'N');
}