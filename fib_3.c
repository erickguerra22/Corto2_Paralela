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

long long int fib_recursive_omp_fix(int n, int threshold) {
    long long int x, y;

    if (n <= 1) {
        return n;
    }

    if (n > threshold) {
        #pragma omp task shared(x)
        {
            x = fib_recursive_omp_fix(n-1, threshold);
        }

        #pragma omp task shared(y)
        {
            y = fib_recursive_omp_fix(n-2, threshold);
        }

        #pragma omp taskwait
    } else {
        x = fib_recursive_omp_fix(n-1, threshold);
        y = fib_recursive_omp_fix(n-2, threshold);
    }

    return x + y;
}


int main(int argc, char *argv[]) {
    int n;
    int threshold = 10;
    int num_threads = 4;
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
    if (argc > 2) {
        if (isNumber(argv[2])) {
            threshold = atoi(argv[2]);
        } else {
            printf("Error: El parámetro 'threshold' no es un número válido. Utilizando valor por defecto: %d\n", threshold);
        }
    }

    if (argc > 3) {
        if (isNumber(argv[3])) {
            num_threads = atoi(argv[3]);
        } else {
            printf("Error: El parámetro 'num_threads' no es un número válido. Utilizando valor por defecto: %d\n", num_threads);
        }
    }

    omp_set_num_threads(num_threads);
    
    start = clock();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib_recursive_omp_fix(n, threshold);
        }
    }


    end = clock();

    finalTime = (double) (end - start) / CLOCKS_PER_SEC;

    printf("El resultado de Fibonacci número %d es %lld\n", n, result);
    printf("Tiempo de ejecución: %f segundos\n", finalTime);

    return 0;
}
