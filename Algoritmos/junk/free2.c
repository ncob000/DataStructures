#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void sumarAyB(int a, int b, int c) {
    c = a + b;
}

void sumarAyBprima(int a, int b, int *c) {
    *c = a + b;
}

int main() {
    int a = 10, b = 15, c = 0;
    
    sumarAyB(a, b, c);
    printf("El resultado de %d + %d = %d\n", a, b, c);

    sumarAyBprima(a, b, &c);
    printf("El resultado de %d + %d = %d\n", a, b, c);
    
    return 0;
}