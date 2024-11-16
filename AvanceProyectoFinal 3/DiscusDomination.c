#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define myInfinite 2147483647
#define TRUE 1
#define FALSE 0
#define RED 1
#define BLACK 0
#define NILKey -2147483647

struct nodeRBTree
{
    int color;
    long long int key;
    struct nodeRBTree *left;
    struct nodeRBTree *right;
    struct nodeRBTree *parent;
};

void inOrderTreeWalk(struct nodeRBTree *x)
{
    if (x->key != NILKey)
    {
        inOrderTreeWalk(x->left);
        if (x->color == RED)
            printf("(%lld, RED) ", x->key);
        else
            printf("(%lld, BLACK) ", x->key);
        printf("%lld ", x->key);
        inOrderTreeWalk(x->right);
    }
}

struct nodeRBTree *treeSearch(struct nodeRBTree *x, int k)
{
    while ((x->key != NILKey) && (k != x->key))
    {
        if (k < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    return x;
}

struct nodeRBTree *treeMinimum(struct nodeRBTree *x)
{
    while (x->left->key != NILKey)
    {
        x = x->left;
    }
    return x;
}

struct nodeRBTree *treeMaximum(struct nodeRBTree *x)
{
    while (x->right->key != NILKey)
    {
        x = x->right;
    }
    return x;
}

struct nodeRBTree *treeSuccessor(struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    if (x->right->key != NILKey)
    {
        return treeMinimum(x->right);
    }
    y = x->parent;
    while ((y->key != NILKey) && (x == y->right))
    {
        x = y;
        y = y->parent;
    }
    return y;
}

struct nodeRBTree *treePredecesor(struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    if (x->left->key != NILKey)
    {
        return treeMaximum(x->left);
    }
    y = x->parent;
    while ((y->key != NILKey) && (x == y->left))
    {
        x = y;
        y = y->parent;
    }
    return y;
}

struct nodeRBTree *AssignNilLeaf()
{
    struct nodeRBTree *w;
    w = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    w->color = BLACK;
    w->key = NILKey;
    w->left = NULL;
    w->right = NULL;

    return w;
}

struct nodeRBTree *LeftRotate(struct nodeRBTree *T, struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    y = x->right;
    x->right = y->left;
    y->left->parent = x;
    y->parent = x->parent;
    if (x->parent->key == NILKey)
    {
        T = y;
    }
    else
    {
        if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;

    return T;
}

struct nodeRBTree *RightRotate(struct nodeRBTree *T, struct nodeRBTree *x)
{
    struct nodeRBTree *y;
    y = x->left;
    x->left = y->right;
    y->right->parent = x;
    y->parent = x->parent;
    if (x->parent->key == NILKey)
    {
        T = y;
    }
    else
    {
        if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
    }
    y->right = x;
    x->parent = y;

    return T;
}

struct nodeRBTree *RB_InsertFixup(struct nodeRBTree *T, struct nodeRBTree *z)
{
    struct nodeRBTree *y;
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    T = LeftRotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                T = RightRotate(T, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    T = RightRotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                T = LeftRotate(T, z->parent->parent);
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
    z->left->parent = z;
    z->right = AssignNilLeaf();
    z->right->parent = z;
    if (T->key != NILKey)
    {
        y = T->parent;
    }
    else
    {
        y = T;
    }
    x = T;

    while (x->key != NILKey)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y->key == NILKey)
    {
        T = z; // Tree T was empty
    }
    else
    {
        free(x);
        if (z->key < y->key)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }
    }
    T = RB_InsertFixup(T, z);
    return T;
}

struct nodeRBTree *RB_DeleteFixup(struct nodeRBTree *T, struct nodeRBTree *x)
{
    struct nodeRBTree *w;
    while ((x != T) && (x->color == BLACK))
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                T = LeftRotate(T, x->parent);
                w = x->parent->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    T = RightRotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                T = LeftRotate(T, x->parent);
                x = T;
            }
        }
        else
        {
            w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                T = RightRotate(T, x->parent);
                w = x->parent->left;
            }
            if ((w->right->color == BLACK) && (w->left->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    T = LeftRotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                T = RightRotate(T, x->parent);
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
    if (z->left->key == NILKey || z->right->key == NILKey)
    {
        y = z;
    }
    else
    {
        y = treeSuccessor(z);
    }
    if (y->left->key != NILKey)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }
    x->parent = y->parent;
    if (y->parent->key == NILKey)
    {
        T = x;
    }
    else
    {
        if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
    }
    if (y != z)
    {
        z->key = y->key;
    }
    if (y->color == BLACK)
    {
        T = RB_DeleteFixup(T, x);
    }
    if (y == y->left->parent)
    {
        free(y->left);
    }
    if (y == y->right->parent)
    {
        free(y->right);
    }

    free(y);
    return T;
}

long long solver(long int n, long int m, long int arr[])
{
    struct nodeRBTree *T = AssignNilLeaf();
    long long max_score = -myInfinite;

    // variable to keep tree values within range m
    int m_range = 0;

    for (int i = 0; i < n; i++)
    {
        // If the tree is out of range, eliminate the oldest value of the tree
        while (m_range < i - m)
        {
            struct nodeRBTree *node_to_delete = treeSearch(T, arr[m_range]);
            if (node_to_delete->key != NILKey)
            {
                T = RB_Delete(T, node_to_delete);
            }
            m_range++;
        }

        if (T->key != NILKey)
        {
            struct nodeRBTree *min_node = treeMinimum(T);
            long long actual_score = arr[i] - min_node->key;

            if (actual_score > max_score)
            {
                max_score = actual_score;
            }
        }
        T = RB_Insert(T, arr[i]);
    }

    return max_score;
}

int main()
{
    long int n, m;
    scanf("%ld %ld", &n, &m);

    long int *arr = (long int *)malloc(n * sizeof(long int));
    for (int i = 0; i < n; i++)
    {
        scanf("%ld", &arr[i]);
    }
    
    long long result = solver(n, m, arr);
    printf("%lld\n", result);

    free(arr);
    return 0;
}
// int main()
// {
//     int max_score = 0, numberOfSquares, maxThrowSquare = 0, temp, cont, squarePoints[numberOfSquares];
//     struct nodeRBTree *T, *m, *x, *y;
//     T = AssignNilLeaf();

//     scanf("%d %d", &numberOfSquares, &maxThrowSquare);
//     for (int i = 0; i < numberOfSquares; i++)
//     {
//         scanf("%d", &squarePoints[i]);
//     }

//     T = RB_Insert(T, squarePoints[0]);

//     for (int j = 1; j <= numberOfSquares; j++)
//     {
//         if (j > maxThrowSquare)
//         {
//             printf(" %d >= %d", j, maxThrowSquare);
//             x = treeSearch(T, squarePoints[j - maxThrowSquare - 1]);
//             T = RB_Delete(T, x);
//         }

//         temp = max_score;
//         m = treeMinimum(T);
//         max_score = squarePoints[j] - m->key;
//         RB_Insert(T, squarePoints[j]);
//         printf("%d\n", max_score);
//     }
//     return 0;
// }