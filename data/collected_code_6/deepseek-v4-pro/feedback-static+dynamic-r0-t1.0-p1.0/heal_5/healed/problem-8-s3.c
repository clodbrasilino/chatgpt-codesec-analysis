#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>

int check_multiplication_overflow(int64_t a, int64_t b, int64_t *result) {
    if (a > 0 && b > 0 && a > INT64_MAX / b) return 1;
    if (a > 0 && b < 0 && b < INT64_MIN / a) return 1;
    if (a < 0 && b > 0 && a < INT64_MIN / b) return 1;
    if (a < 0 && b < 0 && a < INT64_MAX / b) return 1;
    *result = a * b;
    return 0;
}

void square_elements(int64_t *list, int size) {
    for (int i = 0; i < size; i++) {
        int64_t result;
        if (check_multiplication_overflow(list[i], list[i], &result)) {
            fprintf(stderr, "Overflow detected for element at index %d, value %" PRId64 "\n", i, list[i]);
            list[i] = 0;
        } else {
            list[i] = result;
        }
    }
}

int main(void) {
    int size;
    int64_t *list;
    char input_buffer[128];
    long parsed_size;

    printf("Enter number of elements: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    parsed_size = strtol(input_buffer, &endptr, 10);
    if (errno == ERANGE || parsed_size < 1 || parsed_size > 1024 || 
        endptr == input_buffer || *endptr != '\n') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    size = (int)parsed_size;

    list = malloc((size_t)size * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            fprintf(stderr, "Invalid input\n");
            free(list);
            return EXIT_FAILURE;
        }
        errno = 0;
        int64_t val = strtoimax(input_buffer, &endptr, 10);
        if (errno == ERANGE || endptr == input_buffer || *endptr != '\n') {
            fprintf(stderr, "Invalid input\n");
            free(list);
            return EXIT_FAILURE;
        }
        list[i] = val;
    }

    square_elements(list, size);

    printf("Squared elements:\n");
    for (int i = 0; i < size; i++) {
        printf("%" PRId64 " ", list[i]);
    }
    printf("\n");

    free(list);
    return EXIT_SUCCESS;
}