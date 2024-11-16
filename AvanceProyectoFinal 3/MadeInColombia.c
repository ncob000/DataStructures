#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define RED 1
#define BLACK 0
#define NILKey -2147483647

struct nodeRBTree
{
    int key;
    int color;
    int size; /* Variable para guardar el tamano del subarbol*/
    struct nodeRBTree *left;
    struct nodeRBTree *right;
    struct nodeRBTree *p;
};

int getSize(struct nodeRBTree *node)
{
    if (node->key == NILKey)
        return 0;
    return node->size;
}

void updateSize(struct nodeRBTree *node)
{
    if (node->key == NILKey)
        return;
    node->size = getSize(node->left) + getSize(node->right) + 1;
}

struct nodeRBTree *findKth(struct nodeRBTree *root, int k)
{
    if (root->key == NILKey)
        return root;

    int leftSize = getSize(root->left);

    if (k == leftSize)
        return root;
    if (k < leftSize)
        return findKth(root->left, k);
    return findKth(root->right, k - leftSize - 1);
}

void InorderTreeWalk(struct nodeRBTree *x)
{
    if (x->key != NILKey)
    {
        InorderTreeWalk(x->left);
        if (x->color == BLACK)
            printf("( %d, BLACK ) ", x->key);
        else
            printf("( %d, RED ) ", x->key);
        InorderTreeWalk(x->right);
    }
}
struct nodeRBTree *TreeSearch(struct nodeRBTree *x, int k)
{
    while ((x->key != NILKey) && (k != x->key))
    {
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

struct nodeRBTree *TreeMinimum(struct nodeRBTree *x)
{
    while (x->left->key != NILKey)
        x = x->left;
    return x;
}
struct nodeRBTree *TreeMaximum(struct nodeRBTree *x)
{
    while (x->right->key != NILKey)
        x = x->right;
    return x;
}

struct nodeRBTree *TreeSuccessor(struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    if (x->right->key != NILKey)
        return TreeMinimum(x->right);

    y = x->p;
    while ((y->key != NILKey) && (x == y->right))
    {
        x = y;
        y = y->p;
    }
    return y;
}

struct nodeRBTree *TreePredecessor(struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    if (x->left->key != NILKey)
        return TreeMaximum(x->left);
    y = x->p;
    while ((y->key != NILKey) && (x == y->left))
    {
        x = y;
        y = y->p;
    }
    return y;
}

struct nodeRBTree *LeftRotate(struct nodeRBTree *T, struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    y = x->right;
    x->right = y->left;
    y->left->p = x;
    y->p = x->p;
    if (x->p->key == NILKey)
        T = y;
    else
    {
        if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
    }

    y->left = x;
    x->p = y;
    updateSize(x);
    updateSize(y);
    return T;
}
struct nodeRBTree *RightRotate(struct nodeRBTree *T, struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    y = x->left;
    x->left = y->right;
    y->right->p = x;
    y->p = x->p;
    if (x->p->key == NILKey)
        T = y;
    else
    {
        if (x == x->p->right)
            x->p->right = y;
        else
            x->p->left = y;
    }
    y->right = x;
    x->p = y;
    updateSize(x);
    updateSize(y);
    return T;
}

struct nodeRBTree *AssignNilLeaf()
{
    struct nodeRBTree *w;
    w = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    w->color = BLACK;
    w->key = NILKey;
    w->size = 0;
    w->left = NULL;
    w->right = NULL;
    return w;
}

struct nodeRBTree *RB_InsertFixup(struct nodeRBTree *T, struct nodeRBTree *z)
{
    struct nodeRBTree *y;
    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            y = z->p->p->right;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->right)
                {
                    z = z->p;
                    T = LeftRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;

                T = RightRotate(T, z->p->p);
            }
        }
        else
        {
            y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;
                    T = RightRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                T = LeftRotate(T, z->p->p);
            }
        }
    }
    T->color = BLACK;
    return T;
}

struct nodeRBTree *RB_Insert(struct nodeRBTree *T, int k)
{
    struct nodeRBTree *x, *y, *z;
    z = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    z->color = RED;
    z->key = k;
    z->left = AssignNilLeaf();
    z->left->p = z;
    z->right = AssignNilLeaf();
    z->right->p = z;
    if (T->key != NILKey)
        y = T->p;
    else
        y = T;
    x = T;
    while (x->key != NILKey)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if (y->key == NILKey)
        T = z; /* Empty tree . */
    else
    {
        free(x);
        if (z->key < y->key)
            y->left = z;

        else
            y->right = z;
    }
    T = RB_InsertFixup(T, z);

    struct nodeRBTree *current = z;
    while (current->key != NILKey)
    {
        updateSize(current);
        current = current->p;
    }
    return T;
}

struct nodeRBTree *RB_DeleteFixup(struct nodeRBTree *T, struct nodeRBTree *x)
{
    struct nodeRBTree *w;
    while ((x != T) && (x->color == BLACK))
    {
        if (x == x->p->left)
        {
            w = x->p->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                T = LeftRotate(T, x->p);
                w = x->p->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    T = RightRotate(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                T = LeftRotate(T, x->p);
                x = T;
            }
        }
        else
        {
            w = x->p->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                T = RightRotate(T, x->p);
                w = x->p->left;
            }
            if ((w->right->color == BLACK) && (w->left->color == BLACK))
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    T = LeftRotate(T, w);

                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                T = RightRotate(T, x->p);
                x = T;
            }
        }
    }
    x->color = BLACK;
    return T;
}

struct nodeRBTree *RB_Delete(struct nodeRBTree *T, struct nodeRBTree *z)
{
    struct nodeRBTree *x, *y;
    if ((z->left->key == NILKey) || (z->right->key == NILKey))
        y = z;
    else
        y = TreeSuccessor(z);
    if (y->left->key != NILKey)
        x = y->left;
    else
        x = y->right;

    x->p = y->p;
    if (y->p->key == NILKey)
        T = x;
    else
    {
        if (y == y->p->left)
            y->p->left = x;
        else
            y->p->right = x;
    }
    if (y != z)
    {
        z->key = y->key;
        /* Copy all information fields from y to z. */
    }

    if (y->color == BLACK)
        T = RB_DeleteFixup(T, x);
    if (y == y->left->p)
        free(y->left);
    if (y == y->right->p)
        free(y->right);
    free(y);
    return T;
}

double solver(int arr[], int n)
{
    struct nodeRBTree *T = AssignNilLeaf();
    double sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        T = RB_Insert(T, arr[i]);

        int medianPos = i / 2;

        struct nodeRBTree *medianNode = findKth(T, medianPos);
        sum += medianNode->key;
    }

    return round((sum / n) * 100) / 100;
}

int main()
{
    int N;
    while (1)
    {
        scanf("%d", &N);
        if (N == 0)
            break;

        int arr[N];
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &arr[i]);
        }

        double result = solver(arr, N);
        printf("%.2f\n", result);
    }
    return 0;
}