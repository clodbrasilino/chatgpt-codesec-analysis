#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[128];

    printf("Enter number of elements: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (sscanf(input_buffer, "%d", &size) != 1 || size <= 0 || size > 1024) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

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
        /* Possible weaknesses found:
         * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (sscanf(input_buffer, "%" SCNd64, &list[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(list);
            return EXIT_FAILURE;
        }
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