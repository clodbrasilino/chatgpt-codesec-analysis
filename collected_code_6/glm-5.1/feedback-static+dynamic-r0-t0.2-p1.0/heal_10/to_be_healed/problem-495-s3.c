#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input) {
    regex_t regex;
    int ret;
    regmatch_t match;
    size_t capacity;
    size_t length;
    char *result;
    const char *cursor;
    size_t remaining;
    size_t copy_len;
    size_t required;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    remaining = strnlen(input, SIZE_MAX);
    capacity = remaining + 1;
    result = (char *)malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    length = 0;
    cursor = input;

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            remaining = strnlen(cursor, SIZE_MAX);
            required = length + remaining + 1;
            if (required > capacity) {
                capacity = required;
                char *temp = (char *)realloc(result, capacity);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            if (remaining > 0 && remaining <= capacity - length) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + length, cursor, remaining);
            }
            length += remaining;
            break;
        }

        if (match.rm_so > 0) {
            copy_len = match.rm_so;
            required = length + copy_len + 1;
            if (required > capacity) {
                capacity = required;
                char *temp = (char *)realloc(result, capacity);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            if (copy_len <= capacity - length) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + length, cursor, copy_len);
            }
            length += copy_len;
        }

        cursor += match.rm_eo;
    }

    result[length] = '\0';

    char *final_result = (char *)realloc(result, length + 1);
    if (final_result == NULL) {
        regfree(&regex);
        return result;
    }

    regfree(&regex);
    return final_result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    result = remove_lowercase_substrings(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    return 0;
}