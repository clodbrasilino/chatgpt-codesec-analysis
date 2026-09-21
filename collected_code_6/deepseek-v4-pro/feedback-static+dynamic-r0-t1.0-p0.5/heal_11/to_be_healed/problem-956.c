#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>

static char **alloc_failure(char **result, size_t index) {
    for (size_t i = 0; i < index; i++) {
        free(result[i]);
    }
    free(result);
    return NULL;
}

char **split_at_uppercase(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[2];
    char **result = NULL;
    size_t capacity = 0;
    size_t index = 0;
    const char *cursor;
    int status;
    size_t input_len;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    status = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    capacity = 16;
    result = (char **)malloc(sizeof(char *) * capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;

    while (*cursor != '\0') {
        size_t offset = (size_t)(cursor - input);
        /* Possible weaknesses found:
         *  Assuming that condition 'offset>=input_len' is not redundant
         */
        if (offset >= input_len) {
            break;
        }

        status = regexec(&regex, cursor, 2, matches, 0);
        if (status == REG_NOMATCH) {
            /* Possible weaknesses found:
             *  Assignment 'remaining_len=input_len-offset', assigned value is greater than 0
             */
            size_t remaining_len = input_len - offset;
            /* Possible weaknesses found:
             *  Condition 'remaining_len>0' is always true [knownConditionTrueFalse]
             *  Condition 'remaining_len>0' is always true
             */
            if (remaining_len > 0) {
                if (index >= capacity) {
                    size_t new_capacity = capacity * 2;
                    char **temp = (char **)realloc(result, sizeof(char *) * new_capacity);
                    if (temp == NULL) {
                        regfree(&regex);
                        return alloc_failure(result, index);
                    }
                    result = temp;
                    capacity = new_capacity;
                }
                result[index] = (char *)malloc(remaining_len + 1);
                if (result[index] == NULL) {
                    regfree(&regex);
                    return alloc_failure(result, index);
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[index], cursor, remaining_len);
                result[index][remaining_len] = '\0';
                index++;
            }
            break;
        } else if (status == 0) {
            size_t split_pos = (size_t)matches[0].rm_so;
            if (split_pos > 0) {
                if ((size_t)(cursor - input) + split_pos > input_len) {
                    regfree(&regex);
                    return alloc_failure(result, index);
                }
                if (index >= capacity) {
                    size_t new_capacity = capacity * 2;
                    char **temp = (char **)realloc(result, sizeof(char *) * new_capacity);
                    if (temp == NULL) {
                        regfree(&regex);
                        return alloc_failure(result, index);
                    }
                    result = temp;
                    capacity = new_capacity;
                }
                result[index] = (char *)malloc(split_pos + 1);
                if (result[index] == NULL) {
                    regfree(&regex);
                    return alloc_failure(result, index);
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[index], cursor, split_pos);
                result[index][split_pos] = '\0';
                index++;
                cursor += split_pos;
            } else {
                cursor += matches[0].rm_eo;
            }
        } else {
            regfree(&regex);
            return alloc_failure(result, index);
        }
    }

    if (index == 0) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    {
        size_t final_capacity = index + 1;
        if (final_capacity > capacity) {
            char **temp = (char **)realloc(result, sizeof(char *) * final_capacity);
            if (temp == NULL) {
                regfree(&regex);
                return alloc_failure(result, index);
            }
            result = temp;
        }
    }

    result[index] = NULL;
    *count = (int)index;
    regfree(&regex);
    return result;
}

void free_split_result(char **result) {
    if (result == NULL) {
        return;
    }
    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *test_string = "helloWorldExample";
    int count = 0;
    char **parts = split_at_uppercase(test_string, &count);

    if (parts == NULL) {
        printf("Failed to split string\n");
        return 1;
    }

    printf("Split parts (%d):\n", count);
    for (int i = 0; i < count; i++) {
        printf("[%d]: %s\n", i, parts[i]);
    }

    free_split_result(parts);
    return 0;
}