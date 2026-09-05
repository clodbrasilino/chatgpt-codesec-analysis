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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int input;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &input) != 1) {
        return EXIT_FAILURE;
    }
    if (input <= 0 || input % 2 != 0) {
        return EXIT_FAILURE;
    }
    double result = find_average_even(input);
    printf("%.2f\n", result);
    return EXIT_SUCCESS;
}