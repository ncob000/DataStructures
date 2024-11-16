#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    unsigned long long n;

    while (scanf("%lld", &n) && n != 0) {
        // Diagonal k en la que se encuentra el paso n
        unsigned long long k = (long long)floor((-1 + sqrt(1 + 8 * n)) / 2);
        while (k * (k + 1) / 2 < n) {
            k++;
        }

        // Posicion en la diagonal
        unsigned long long boxesBeforeDiagonal = k * (k - 1) / 2;
        unsigned long long positionInDiagonal = n - boxesBeforeDiagonal;

        unsigned long long row, col;
        if (k % 2 == 0) {
            // Diagonal par, movimiento hacia abajo-derecha
            row = positionInDiagonal;
            col = k + 1 - positionInDiagonal;
        } else {
            // Diagonal impar, movimiento hacia arriba-izquierda
            row = k + 1 - positionInDiagonal;
            col = positionInDiagonal;
        }

        printf("%lld %lld\n", row, col);
    }

    return 0;
}
