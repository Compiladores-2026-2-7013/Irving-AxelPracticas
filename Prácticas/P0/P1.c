//Aqui hacemos la  ultima parte de la practica 1
#include <stdio.h>   // Directiva 1

// Directiva 2
#define SUMA(a, b) ((a) + (b))

// Directiva 3
#ifdef _DEBUG
    #define MENSAJE "Modo activado"
#else
    #define MENSAJE "Modo desactivado"
#endif

// Directiva 4
#ifndef PI
    #define PI 3.1416
#endif

int main() {
    int x = 5, y = 3;
    printf("La suma de %d y %d es: %d\n", x, y, SUMA(x, y));
    printf("Mensaje: %s\n", MENSAJE);
    printf("Valor de PI: %.4f\n", PI);

    return 0;
}
