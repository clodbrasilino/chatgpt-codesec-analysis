#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int find_min_flips(const char *binary_string) {
    if (binary_string == NULL) {
        return -1;
    }

    size_t length = strlen(binary_string);
    if (length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; i++) {
        if (binary_string[i] != '0' && binary_string[i] != '1') {
            return -1;
        }
    }

    int flips_starting_with_0 = 0;
    int flips_starting_with_1 = 0;

    for (size_t i = 0; i < length; i++) {
        char expected_0 = (i % 2 == 0) ? '0' : '1';
        char expected_1 = (i % 2 == 0) ? '1' : '0';

        if (binary_string[i] != expected_0) {
            flips_starting_with_0++;
        }
        if (binary_string[i] != expected_1) {
            flips_starting_with_1++;
        }
    }

    return min(flips_starting_with_0, flips_starting_with_1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = find_min_flips(argv[1]);
    if (result == -1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}