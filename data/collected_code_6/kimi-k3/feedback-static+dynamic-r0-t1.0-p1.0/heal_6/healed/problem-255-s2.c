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

static int read_positive_int(const char *prompt, int max_value, int *result) {
    char buffer[64];
    char *endptr;
    long val;
    
    if (prompt == NULL || result == NULL || max_value <= 0) {
        return -1;
    }
    
    if (printf("%s", prompt) < 0) {
        return -1;
    }
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }
    
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return -1;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return -1;
    }
    
    if (val <= 0 || val > max_value || val > INT_MAX) {
        return -1;
    }
    
    *result = (int)val;
    return 0;
}

int main(void) {
    int n = 3;
    int k;
    int *combination;
    
    if (read_positive_int("Enter number of positions to fill: ", 20, &k) != 0) {
        fprintf(stderr, "Invalid input\n");
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
        return EXIT_FAILURE;
    }
    
    free(combination);
    
    return EXIT_SUCCESS;
}