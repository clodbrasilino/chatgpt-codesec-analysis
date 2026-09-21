#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

int maxDifference(const char *str) {
    int max_diff = INT_MIN;
    int current_diff = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        int value = (str[i] == '0') ? 1 : -1;
        current_diff += value;
        
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
        
        if (current_diff < 0) {
            current_diff = 0;
        }
    }
    
    return max_diff;
}

int main(void) {
    char *binary_str = NULL;
    size_t buffer_size = 1001;
    size_t input_len;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;

    binary_str = (char *)malloc(buffer_size * sizeof(char));
    if (binary_str == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter a binary string: ");
    if (fgets(binary_str, (int)buffer_size, stdin) == NULL) {
        printf("Error reading input\n");
        free(binary_str);
        return 1;
    }

    binary_str[buffer_size - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(binary_str);

    if (input_len > 0 && binary_str[input_len - 1] == '\n') {
        binary_str[input_len - 1] = '\0';
        input_len--;
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    if (binary_str[0] == '\0') {
        printf("Empty string\n");
        free(binary_str);
        return 1;
    }

    if (input_len >= 1000) {
        printf("Input too long\n");
        free(binary_str);
        return 1;
    }

    for (size_t i = 0; i < input_len && binary_str[i] != '\0'; i++) {
        if (binary_str[i] != '0' && binary_str[i] != '1') {
            printf("Invalid input: string must contain only 0s and 1s\n");
            free(binary_str);
            return 1;
        }
    }

    int result = maxDifference(binary_str);
    printf("Maximum difference (0s - 1s): %d\n", result);

    free(binary_str);
    return 0;
}