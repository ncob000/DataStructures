#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define myInfinite 2147483647
#define TRUE 1
#define FALSE 0
#define RED 1
#define BLACK 0
#define NILKey NULL  // Nil key será un puntero NULL

struct nodeRBTree
{
    int color;
    char *key;  // Cambiado de int a char*
    struct nodeRBTree *left;
    struct nodeRBTree *right;
    struct nodeRBTree *parent;
};

void inOrderTreeWalk(struct nodeRBTree *x){
    if(x->key != NILKey){
        inOrderTreeWalk(x->left);
        if(x->color == RED)
            printf("(%s, RED) ", x->key);
        else
            printf("(%s, BLACK) ", x->key);
        printf("%s ", x->key);
        inOrderTreeWalk(x->right);
    }
}

struct nodeRBTree *treeSearch(struct nodeRBTree *x, char *k){
    while((x->key != NILKey) && (strcmp(k, x->key) != 0)){
        if(strcmp(k, x->key) < 0){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    return x;
}

struct nodeRBTree *treeMinimum(struct nodeRBTree *x){
    while(x->left->key != NILKey){
        x = x->left;
    }
    return x;
}

struct nodeRBTree *treeMaximum(struct nodeRBTree *x){
    while(x->right->key != NILKey){
        x = x->right;
    }
    return x;
}

struct nodeRBTree *treeSuccessor(struct nodeRBTree *x){
    struct nodeRBTree *y;
    if(x->right->key != NILKey){
        return treeMinimum(x->right);
    }
    y = x->parent;
    while((y->key != NILKey) && (x == y->right)){
        x = y;
        y = y->parent;
    }
    return y;
}

struct nodeRBTree *treePredecesor(struct nodeRBTree *x){
    struct nodeRBTree *y;
    if(x->left->key != NILKey){
        return treeMaximum(x->left);
    }
    y = x->parent;
    while((y->key != NILKey) && (x == y->left)){
        x = y;
        y = y->parent;
    }
    return y;
}

struct nodeRBTree *AssignNilLeaf(){
    struct nodeRBTree *w;
    w = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    w->color = BLACK;
    w->key = NILKey;
    w->left = NULL;
    w->right = NULL;
    return w;
}

struct nodeRBTree *LeftRotate(struct nodeRBTree *T, struct nodeRBTree *x){
    struct nodeRBTree *y;
    y = x->right;
    x->right = y->left;
    y->left->parent = x;
    y->parent = x->parent;
    if(x->parent->key == NILKey){
        T = y;
    }else{
        if(x == x->parent->left){
            x->parent->left = y;
        }else{
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
    return T;
}

struct nodeRBTree *RightRotate(struct nodeRBTree *T, struct nodeRBTree *x){
    struct nodeRBTree *y;
    y = x->left;
    x->left = y->right;
    y->right->parent = x;
    y->parent = x->parent;
    if(x->parent->key == NILKey){
        T = y;
    }else{
        if(x == x->parent->right){
            x->parent->right = y;
        }else{
            x->parent->left = y;
        }
    }
    y->right = x;
    x->parent = y;
    return T;
}

struct nodeRBTree *RB_InsertFixup(struct nodeRBTree *T, struct nodeRBTree *z){
    struct nodeRBTree *y;
    while(z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->right){
                    z = z->parent;
                    T = LeftRotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                T = RightRotate(T, z->parent->parent);
            }
        }else{
            y = z->parent->parent->left;
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->left){
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

struct nodeRBTree *RB_Insert(struct nodeRBTree *T, char *k){
    struct nodeRBTree *x, *y, *z;
    z = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    z->color = RED;
    z->key = strdup(k);  // Copia de la cadena
    z->left = AssignNilLeaf();
    z->left->parent = z;
    z->right = AssignNilLeaf();
    z->right->parent = z;
    if (T->key != NILKey){
        y = T->parent;
    }
    else{
        y = T;
    }
    x = T;

    while(x->key != NILKey){
        y = x;
        if(strcmp(z->key, x->key) < 0){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y->key == NILKey){
        T = z; // Tree T was empty
    }else{
        free(x);
        if(strcmp(z->key, y->key) < 0){
            y->left = z;
        }else{
            y->right = z;
        }
    }
    T = RB_InsertFixup(T, z);
    return T;
}

struct nodeRBTree *RB_DeleteFixup(struct nodeRBTree *T, struct nodeRBTree *x) {
    struct nodeRBTree *w;    
    
    while (x != T && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;

            if (w->color == RED) {
                w->color = BLACK;             
                x->parent->color = RED;        
                T = LeftRotate(T, x->parent); 
                w = x->parent->right;           
            }
            
          
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;    
                x = x->parent;     
            } else {
            
                if (w->right->color == BLACK) {
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
        } else {
     
            w = x->parent->left;
            
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                T = RightRotate(T, x->parent);
                w = x->parent->left;
            }
            
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
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


struct nodeRBTree *RB_Delete(struct nodeRBTree *T, struct nodeRBTree *z){
    struct nodeRBTree *x, *y;
    if(z->left->key == NILKey || z->right->key == NILKey){
        y = z;
    }else{
        y = treeSuccessor(z);
    }
    if(y->left->key != NILKey){
        x = y->left;
    }else{
        x = y->right;
    }
    x->parent = y->parent;
    if(y->parent->key == NILKey){
        T = x;
    }else{
        if(y == y->parent->left){
            y->parent->left = x;
        }else{
            y->parent->right = x;
        }
    }
    if(y != z){
        free(z->key); // Liberamos la memoria de la clave
        z->key = strdup(y->key);  // Copiamos la clave de y a z
    }
    if(y->color == BLACK){
        T = RB_DeleteFixup(T, x);
    }
    if(y == y->left->parent){
        free(y->key);
        free(y);
    }
    return T;
}


int main() {
    struct nodeRBTree *T = (struct nodeRBTree *)malloc(sizeof(struct nodeRBTree));
    T->key = NILKey;  // El árbol comienza vacío
    T->color = BLACK;
    T->left = NULL;
    T->right = NULL;
    T->parent = NULL;

    // Insertando algunas cadenas en el árbol
    printf("Insertando 'apple'\n");
    T = RB_Insert(T, "apple");
    printf("Insertando 'banana'\n");
    T = RB_Insert(T, "banana");
    printf("Insertando 'cherry'\n");
    T = RB_Insert(T, "cherry");
    printf("Insertando 'date'\n");
    T = RB_Insert(T, "date");
    printf("Insertando 'elderberry'\n");
    T = RB_Insert(T, "elderberry");
    inOrderTreeWalk(T);
    printf("\n");

    // Buscando un elemento en el árbol
    printf("\nBuscando 'cherry':\n");
    struct nodeRBTree *result = treeSearch(T, "cherry");
    if (result != NULL) {
        printf("Elemento encontrado: %s\n", result->key);
    } else {
        printf("Elemento no encontrado\n");
    }

    // Eliminando un elemento
    printf("\nEliminando 'banana'\n");
    struct nodeRBTree *nodeToDelete = treeSearch(T, "banana");
    T = RB_Delete(T, nodeToDelete);

    // Mostramos el árbol después de la eliminación
    printf("\nCaminata en orden del árbol después de eliminación:\n");
    inOrderTreeWalk(T);
    printf("\n");

    return 0;
}

// Definir las funciones aquí (las mismas funciones de tu código anterior)
