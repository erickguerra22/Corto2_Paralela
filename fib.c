#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool isNumber(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

long long int fib_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main(int argc, char *argv[]) {
    int n;
    long long int result;
    clock_t start, end;
    double finalTime;

    if (argc > 1) {
        if (isNumber(argv[1])) {
            n = atoi(argv[1]);
        } else {
            printf("Error: El parámetro ingresado no es un número válido.\n");
            return 1;
        }
    }

    start = clock();

    result = fib_recursive(n);

    end = clock();

    finalTime = (double) (end - start) / CLOCKS_PER_SEC;

    printf("El resultado de Fibonacci número %d es %lld\n", n, result);
    printf("Tiempo de ejecución: %f segundos\n", finalTime);

    return 0;
}
