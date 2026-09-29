#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int average_of_even_till(int target) {
    if (target <= 0 || target % 2 != 0) {
        return -1;
    }

    long long count = target / 2;
    if (count == 0) {
        return -1;
    }

    long long sum = count * (count + 1);
    long long avg = sum / count;

    if (avg > INT_MAX || avg < INT_MIN) {
        return -1;
    }

    return (int)avg;
}

int main(int argc, char *argv[]) {
    char input[32];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[sizeof(input) - 2] != '\0' && input[sizeof(input) - 2] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    char *endptr;
    long val = strtol(input, &endptr, 10);

    if (endptr == input) {
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (*endptr != ' ' && *endptr != '\t' && *endptr != '\r') {
            return EXIT_FAILURE;
        }
        endptr++;
    }

    if (val > INT_MAX || val < INT_MIN) {
        return EXIT_FAILURE;
    }

    int target = (int)val;
    int result = average_of_even_till(target);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}