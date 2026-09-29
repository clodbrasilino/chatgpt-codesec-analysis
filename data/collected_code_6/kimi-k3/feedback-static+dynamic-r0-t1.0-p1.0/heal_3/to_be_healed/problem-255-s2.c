#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

static int generate_combinations(int *combination, int index, int k, int num_colors) {
    int i;
    
    if (combination == NULL || index < 0 || k <= 0 || num_colors <= 0 || index > k) {
        return -1;
    }
    
    if (index == k) {
        for (i = 0; i < k; i++) {
            if (printf("%d", combination[i]) < 0) {
                return -1;
            }
            if (i < k - 1) {
                if (printf(" ") < 0) {
                    return -1;
                }
            }
        }
        if (printf("\n") < 0) {
            return -1;
        }
        return 0;
    }
    
    for (i = 0; i < num_colors; i++) {
        combination[index] = i;
        if (generate_combinations(combination, index + 1, k, num_colors) != 0) {
            return -1;
        }
    }
    
    return 0;
}

int main(void) {
    int n = 3;
    int k;
    int *combination;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long val;
    
    printf("Enter number of positions to fill: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (val <= 0 || val > INT_MAX) {
        fprintf(stderr, "Number of positions must be positive and within range\n");
        return EXIT_FAILURE;
    }
    
    k = (int)val;
    
    if (k > 20) {
        fprintf(stderr, "Number of positions too large (maximum 20)\n");
        return EXIT_FAILURE;
    }
    
    if ((size_t)k > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Number of positions too large\n");
        return EXIT_FAILURE;
    }
    
    combination = (int *)calloc((size_t)k, sizeof(int));
    if (combination == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("All combinations with repetition:\n");
    
    if (generate_combinations(combination, 0, k, n) != 0) {
        fprintf(stderr, "Error generating combinations\n");
        free(combination);
        combination = NULL;
        return EXIT_FAILURE;
    }
    
    free(combination);
    combination = NULL;
    
    return EXIT_SUCCESS;
}