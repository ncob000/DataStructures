#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define RED 1
#define BLACK 0
#define MAX_STRING_LENGTH 100
#define NIL_STRING ""

int position = 0;

struct nodeRBTree
{
  int color;
  char *key;
  int position;
  struct nodeRBTree *left;
  struct nodeRBTree *right;
  struct nodeRBTree *parent;
};

void inOrderTreeWalk(struct nodeRBTree *x)
{
  if (strcmp(x->key, NIL_STRING) != 0)
  {
    inOrderTreeWalk(x->left);
    if (x->color == RED)
      printf("(%s, RED) ", x->key);
    else
      printf("(%s, BLACK) ", x->key);
    inOrderTreeWalk(x->right);
  }
}

void AssignPositions(struct nodeRBTree *x)
{
  if (strcmp(x->key, NIL_STRING) != 0)
  {
    AssignPositions(x->left);
    position++;
    x->position = position;
    AssignPositions(x->right);
  }
}

struct nodeRBTree *treeSearch(struct nodeRBTree *x, const char *k)
{
  while ((strcmp(x->key, NIL_STRING) != 0) && (strcmp(k, x->key) != 0))
  {
    if (strcmp(k, x->key) < 0)
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
  while (strcmp(x->left->key, NIL_STRING) != 0)
  {
    x = x->left;
  }
  return x;
}

struct nodeRBTree *treeMaximum(struct nodeRBTree *x)
{
  while (strcmp(x->right->key, NIL_STRING) != 0)
  {
    x = x->right;
  }
  return x;
}

struct nodeRBTree *treeSuccessor(struct nodeRBTree *x)
{
  struct nodeRBTree *y;
  if (strcmp(x->right->key, NIL_STRING) != 0)
  {
    return treeMinimum(x->right);
  }
  y = x->parent;
  while ((strcmp(y->key, NIL_STRING) != 0) && (x == y->right))
  {
    x = y;
    y = y->parent;
  }
  return y;
}

struct nodeRBTree *treePredecesor(struct nodeRBTree *x)
{
  struct nodeRBTree *y;
  if (strcmp(x->left->key, NIL_STRING) != 0)
  {
    return treeMaximum(x->left);
  }
  y = x->parent;
  while ((strcmp(y->key, NIL_STRING) != 0) && (x == y->left))
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
  w->key = (char *)malloc(sizeof(char));
  strcpy(w->key, NIL_STRING);
  w->left = NULL;
  w->right = NULL;
  return w;
}

// Las funciones de rotación no necesitan cambios ya que operan sobre la estructura del árbol
struct nodeRBTree *LeftRotate(struct nodeRBTree *T, struct nodeRBTree *x)
{
  struct nodeRBTree *y;
  y = x->right;
  x->right = y->left;
  y->left->parent = x;
  y->parent = x->parent;
  if (strcmp(x->parent->key, NIL_STRING) == 0)
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
  if (strcmp(x->parent->key, NIL_STRING) == 0)
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

struct nodeRBTree *RB_Insert(struct nodeRBTree *T, const char *k)
{
  struct nodeRBTree *x, *y, *z;
  z = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
  z->color = RED;
  z->key = (char *)malloc((strlen(k) + 1) * sizeof(char));
  strcpy(z->key, k);
  z->left = AssignNilLeaf();
  z->left->parent = z;
  z->right = AssignNilLeaf();
  z->right->parent = z;

  if (strcmp(T->key, NIL_STRING) != 0)
  {
    y = T->parent;
  }
  else
  {
    y = T;
  }
  x = T;

  while (strcmp(x->key, NIL_STRING) != 0)
  {
    y = x;
    if (strcmp(z->key, x->key) < 0)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }

  z->parent = y;
  if (strcmp(y->key, NIL_STRING) == 0)
  {
    T = z; // Tree T was empty
  }
  else
  {
    free(x->key);
    free(x);
    if (strcmp(z->key, y->key) < 0)
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
  if (strcmp(z->left->key, NIL_STRING) == 0 || strcmp(z->right->key, NIL_STRING) == 0)
  {
    y = z;
  }
  else
  {
    y = treeSuccessor(z);
  }

  if (strcmp(y->left->key, NIL_STRING) != 0)
  {
    x = y->left;
  }
  else
  {
    x = y->right;
  }

  x->parent = y->parent;
  if (strcmp(y->parent->key, NIL_STRING) == 0)
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
    free(z->key);
    z->key = (char *)malloc((strlen(y->key) + 1) * sizeof(char));
    strcpy(z->key, y->key);
    z->position = y->position;
  }

  if (y->color == BLACK)
  {
    T = RB_DeleteFixup(T, x);
  }

  if (y == y->left->parent)
  {
    free(y->left->key);
    free(y->left);
  }
  if (y == y->right->parent)
  {
    free(y->right->key);
    free(y->right);
  }

  free(y->key);
  free(y);
  return T;
}

 