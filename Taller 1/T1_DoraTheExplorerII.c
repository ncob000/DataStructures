#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int x, y;
    while (scanf("%d %d", &x, &y) && (x != 0 && y != 0)){
        // Calculo de la diagonal
        long long int diagonal = x + y - 1;
        // Calculo del numero de pasos hasta la diagonal d-1
        long long int stepsBefore = (diagonal - 1) * diagonal / 2;
        long long int result;

        if (diagonal % 2 == 0) {
            result = stepsBefore + x;
        } else {
            result = stepsBefore + y;
        }
        printf("%lld\n", result);
    }

    return 0;
}
