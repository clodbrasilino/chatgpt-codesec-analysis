#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_diff_zeros_ones(const char *binary_str) {
    if (binary_str == NULL) {
        return 0;
    }

    size_t len = strlen(binary_str);
    if (len == 0) {
        return 0;
    }

    int max_diff = 0;
    int current_diff = 0;

    for (size_t i = 0; i < len; ++i) {
        int val = (binary_str[i] == '0') ? 1 : -1;
        
        if (current_diff + val > val) {
            current_diff += val;
        } else {
            current_diff = val;
        }
        
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
    }

    return max_diff;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_str = argv[1];
    size_t len = strlen(input_str);
    
    for (size_t i = 0; i < len; ++i) {
        if (input_str[i] != '0' && input_str[i] != '1') {
            fprintf(stderr, "Error: Input string must contain only '0' and '1'\n");
            return EXIT_FAILURE;
        }
    }

    int result = max_diff_zeros_ones(input_str);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}