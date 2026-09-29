#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool has_increasing_trend(const int *sequence, size_t length) {
    if (sequence == NULL) {
        return false;
    }

    if (length < 2) {
        return true;
    }

    for (size_t i = 1; i < length; ++i) {
        if (sequence[i] <= sequence[i - 1]) {
            return false;
        }
    }

    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    size_t length = (size_t)(argc - 1);
    int *sequence = (int *)malloc(length * sizeof(int));
    if (sequence == NULL) {
        return 1;
    }

    for (size_t i = 0; i < length; ++i) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(sequence);
            return 1;
        }
        sequence[i] = (int)val;
    }

    bool result = has_increasing_trend(sequence, length);
    printf("%s\n", result ? "Increasing" : "Not Increasing");

    free(sequence);
    return 0;
}