#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    char *p, *q;
    int n = 12;
    p = (char *) malloc(n);
    strcpy(p, "Pascal");

    q = (char *) malloc(n);
    strcpy(q, "Lenguaje C");

    printf("%s %s\n", p, q);
    free(q);
    printf("%s %s\n", p, q);
    q = p;
    printf("%s %s\n", p, q);
    return 0;
}