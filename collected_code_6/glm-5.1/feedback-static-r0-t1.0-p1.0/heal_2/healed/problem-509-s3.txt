#include <stdio.h>
#include <stdlib.h>

double average_of_odds(int n) {
    if (n <= 0 || n % 2 == 0) {
        return 0.0;
    }
    int count = (n / 2) + 1;
    double sum = (double)count * count;
    return sum / count;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <odd_number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val <= 0 || val % 2 != 0 || val > 2147483647) {
        fprintf(stderr, "Error: Argument must be a positive odd integer within int range.\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    double avg = average_of_odds(n);
    printf("%f\n", avg);
    return EXIT_SUCCESS;
}