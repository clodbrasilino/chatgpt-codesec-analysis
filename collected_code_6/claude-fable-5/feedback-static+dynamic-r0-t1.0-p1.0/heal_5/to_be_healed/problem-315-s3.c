#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT 1024

int find_first_max_even_word(const char *str, size_t str_max, char *result, size_t result_size)
{
    size_t i = 0;
    size_t len = 0;
    size_t max_len = 0;
    size_t best_start = 0;
    int found = 0;

    if (str == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    len = strnlen(str, str_max);

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }
        {
            size_t start = i;
            size_t word_len = 0;

            while (i < len && !isspace((unsigned char)str[i])) {
                i++;
            }
            word_len = i - start;

            if ((word_len % 2u) == 0u && word_len > max_len) {
                max_len = word_len;
                best_start = start;
                found = 1;
            }
        }
    }

    if (found == 0) {
        return -1;
    }

    if (max_len >= result_size) {
        return -1;
    }

    if (best_start > len || max_len > len - best_start) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, &str[best_start], max_len);
    result[max_len] = '\0';

    return (int)max_len;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[MAX_INPUT];
    int ret = 0;

    memset(input, 0, sizeof(input));
    memset(result, 0, sizeof(result));

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';
    input[strcspn(input, "\n")] = '\0';

    ret = find_first_max_even_word(input, sizeof(input), result, sizeof(result));

    if (ret < 0) {
        printf("No even length word found\n");
    } else {
        printf("First maximum even length word: %s (length %d)\n", result, ret);
    }

    return EXIT_SUCCESS;
}