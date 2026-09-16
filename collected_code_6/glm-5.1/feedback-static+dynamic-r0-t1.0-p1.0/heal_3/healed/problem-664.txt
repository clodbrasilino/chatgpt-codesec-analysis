#include <stdio.h>
#include <stdlib.h>

double find_average_even(int max_even) {
    if (max_even <= 0 || max_even % 2 != 0) {
        return 0.0;
    }
    long long count = (long long)max_even / 2;
    long long sum = count * (count + 1);
    return (double)sum / (double)count;
}

int main(int argc, const char * const argv[]) {
    int input;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <even_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &input) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (input <= 0 || input % 2 != 0) {
        fprintf(stderr, "Input must be a positive even integer\n");
        return EXIT_FAILURE;
    }
    double result = find_average_even(input);
    printf("%.2f\n", result);
    return EXIT_SUCCESS;
}