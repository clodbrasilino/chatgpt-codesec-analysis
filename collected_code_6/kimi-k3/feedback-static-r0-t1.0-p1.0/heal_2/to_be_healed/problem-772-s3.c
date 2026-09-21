#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char *remove_k_length_words(const char *str, size_t k) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (str[len] != '\0' && len < SIZE_MAX - 1) {
        len++;
    }

    if (len == SIZE_MAX - 1 && str[len] != '\0') {
        return NULL;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'prev_word_removed' can be reduced. [variableScope]
     *  Variable 'prev_word_removed' is assigned a value that is never used. [unreadVariable]
     */
    int prev_word_removed = 0;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }

        if (i >= len) {
            break;
        }

        size_t word_start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }

        size_t word_len = i - word_start;

        if (word_len != k) {
            if (j > 0) {
                if (j >= len) {
                    free(result);
                    return NULL;
                }
                result[j++] = ' ';
            }
            
            if (j + word_len > len) {
                free(result);
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + j, str + word_start, word_len);
            j += word_len;
            /* Possible weaknesses found:
             *  Value stored to 'prev_word_removed' is never read [deadcode.DeadStores]
             *  Variable 'prev_word_removed' is assigned a value that is never used. [unreadVariable]
             */
            prev_word_removed = 0;
        } else {
            /* Possible weaknesses found:
             *  Value stored to 'prev_word_removed' is never read [deadcode.DeadStores]
             *  Variable 'prev_word_removed' is assigned a value that is never used. [unreadVariable]
             */
            prev_word_removed = 1;
        }
    }

    result[j] = '\0';

    char *final_result = (char *)realloc(result, j + 1);
    if (final_result == NULL) {
        return result;
    }

    return final_result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    size_t k;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t input_len = 0;
    while (input_len < sizeof(input) - 1 && input[input_len] != '\0') {
        input_len++;
    }
    
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
    }

    printf("Enter the word length to remove: ");
    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Invalid input for k\n");
        return EXIT_FAILURE;
    }

    char *result = remove_k_length_words(input, k);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}