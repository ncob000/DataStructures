#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// En la variable p está almacenada una dirección que apunta a un bloque de 10 bytes.
void ex1() {
    char *p;
    int n = 10;
    p = (char *)malloc(n);
    strcpy(p, "Sencillo");
    printf("%s\n", p);    
}

// Ejemplo 2:Almacenar el número entero 821 en una localización de memoria asignada por la función malloc().
void ex2(){
    int *p;
    p = (int *)malloc(sizeof(int));
    printf("Size in bites of data-type integer: %d\n", sizeof(int));

    printf("Direccion de memoria apuntada por el puntero p: %d\n", p);
    *p = 821;
    printf("Direccion de memoria apuntada por el puntero p: %d\n", p);
    /*
        Despues de modificar el contenido del puntero no cambia su direccion de memoria
    */
    printf("Contenido del bloque apuntado por p: %d\n", *p); // Contenido de lo que esta almacenado en la direccion de memoria


}

typedef struct R {
    int a;
    float b;
    double c;
    char *p;
} estructura;

void ex3(){

    printf("Size in bytes data.type integer: %d\n", sizeof(int));
    printf("Size in bytes data.type float: %d\n", sizeof(float));
    printf("Size in bytes data.type double: %d\n", sizeof(double));
    printf("Size in bytes data.type long long int: %d\n", sizeof(long long int));
    printf("Size in bytes data.type char: %d\n", sizeof(char));
    printf("Size in bytes data.type estructura: %d\n", sizeof(estructura));
    
    int n = 10;
    estructura *q;
    q = (estructura *)malloc(sizeof(estructura));
    q->a = 8;
    q->b = 10.31;
    q->c = 10.32;
    q->p = (char *)malloc(n);
    strcpy(q->p, "Cadena");
    printf("%d %.2f %.2lf %s",q->a, q->b, q->c, q->p);
}

int main () {
    // ex1();
    // ex2();
    ex3();
    return 0;
}