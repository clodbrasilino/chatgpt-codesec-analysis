#include <stdio.h>
#include <stdlib.h>

double find_average_odd(int limit) {
    if (limit <= 0 || limit % 2 == 0) {
        return 0.0;
    }

    long long count = 0;
    long long sum = 0;

    for (int i = 1; i <= limit; i += 2) {
        sum += i;
        count++;
    }

    if (count == 0) {
        return 0.0;
    }

    return (double)sum / (double)count;
}

int main(int argc, char const * const * argv) {
    int limit;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%d", &limit) != 1) {
        return EXIT_FAILURE;
    }

    if (limit <= 0 || limit % 2 == 0) {
        return EXIT_FAILURE;
    }

    double average = find_average_odd(limit);
    printf("%.2f\n", average);

    return EXIT_SUCCESS;
}