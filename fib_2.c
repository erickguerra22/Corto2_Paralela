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

long long int fib_recursive_omp(int n) {
    long long int x, y;

    if (n <= 1) {
        return n;
    }

    #pragma omp task shared(x)
    {
        x = fib_recursive_omp(n-1);
    }
    
    #pragma omp task shared(y)
    {
        y = fib_recursive_omp(n-2);
    }

    #pragma omp taskwait

    return x + y;
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

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib_recursive_omp(n);
        }
    }

    end = clock();

    finalTime = (double) (end - start) / CLOCKS_PER_SEC;

    printf("El resultado de Fibonacci número %d es %lld\n", n, result);
    printf("Tiempo de ejecución: %f segundos\n", finalTime);

    return 0;
}
