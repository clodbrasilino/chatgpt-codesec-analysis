#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string(const char *str, size_t str_len, const char *pattern, int *count) {
    regex_t regex;
    regmatch_t match;
    char **result = NULL;
    int capacity = 10;
    int size = 0;
    const char *current = str;
    size_t remaining = str_len;
    int ret;

    if (str == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (remaining > 0) {
        ret = regexec(&regex, current, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            break;
        }

        if (match.rm_so > 0) {
            if (size >= capacity) {
                char **temp;
                capacity *= 2;
                temp = realloc(result, capacity * sizeof(char *));
                if (temp == NULL) {
                    goto cleanup;
                }
                result = temp;
            }

            size_t len = (size_t)match.rm_so;
            if (len > remaining) {
                goto cleanup;
            }
            result[size] = malloc(len + 1);
            if (result[size] == NULL) {
                goto cleanup;
            }
            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[size], current, len);
            }
            result[size][len] = '\0';
            size++;
        }

        if ((size_t)match.rm_eo > remaining) {
            goto cleanup;
        }
        current += match.rm_eo;
        remaining -= (size_t)match.rm_eo;
    }

    /* Possible weaknesses found:
     *  outer condition: remaining>0
     */
    if (remaining > 0) {
        if (size >= capacity) {
            char **temp;
            capacity += 1;
            temp = realloc(result, capacity * sizeof(char *));
            if (temp == NULL) {
                goto cleanup;
            }
            result = temp;
        }

        /* Possible weaknesses found:
         *  'len' is assigned value 'remaining' here.
         */
        size_t len = remaining;
        result[size] = malloc(len + 1);
        if (result[size] == NULL) {
            goto cleanup;
        }
        /* Possible weaknesses found:
         *  identical inner condition: len>0
         *  Identical inner 'if' condition is always true. [identicalInnerCondition]
         */
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[size], current, len);
        }
        result[size][len] = '\0';
        size++;
    }

    regfree(&regex);
    *count = size;
    return result;

cleanup:
    for (int i = 0; i < size; i++) {
        free(result[i]);
    }
    free(result);
    regfree(&regex);
    return NULL;
}

void free_split_result(char **result, int count) {
    if (result == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *input = "apple,banana;cherry:grape|orange";
    const char *pattern = "[,;:|]";
    int count = 0;
    char **tokens;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    tokens = split_string(input, strlen(input), pattern, &count);
    
    if (tokens == NULL) {
        fprintf(stderr, "Error splitting string\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
    }

    free_split_result(tokens, count);
    return EXIT_SUCCESS;
}