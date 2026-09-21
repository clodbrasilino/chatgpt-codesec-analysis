#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *convert_tuple_to_list(const char *tuple_str, const char *suffix, int *out_len) {
    if (!tuple_str || !suffix || !out_len) {
        return NULL;
    }

    size_t tuple_len = strnlen(tuple_str, 4096);
    if (tuple_len >= 4096 || tuple_len < 2 || tuple_str[0] != '(' || tuple_str[tuple_len - 1] != ')') {
        *out_len = 0;
        return NULL;
    }

    size_t content_len = tuple_len - 2;
    char *content = (char *)malloc(content_len + 1);
    if (!content) {
        *out_len = 0;
        return NULL;
    }

    if (content_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(content, tuple_str + 1, content_len);
    }
    content[content_len] = '\0';

    size_t suffix_len = strnlen(suffix, 256);
    if (suffix_len >= 256) {
        free(content);
        *out_len = 0;
        return NULL;
    }

    size_t capacity = 64;
    size_t length = 0;
    char *result = (char *)malloc(capacity);
    if (!result) {
        free(content);
        *out_len = 0;
        return NULL;
    }
    result[0] = '\0';

    char *saveptr;
    char *token = strtok_r(content, ",", &saveptr);
    int first = 1;

    while (token) {
        while (*token == ' ') token++;

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        char *end = token + strlen(token);
        /* Possible weaknesses found:
         *  Assuming that condition 'end>token' is not redundant
         */
        while (end > token && *(end - 1) == ' ') {
            end--;
        }
        /* Possible weaknesses found:
         *  Assignment 'token_len=(unsigned long)(end-token)', assigned value is less than 1
         */
        size_t token_len = (size_t)(end - token);

        /* Possible weaknesses found:
         *  Assignment 'entry_len=token_len+suffix_len+1', assigned value is greater than 0
         */
        size_t entry_len = token_len + suffix_len + 1;
        /* Possible weaknesses found:
         *  Condition 'entry_len<token_len' is always false [knownConditionTrueFalse]
         *  Condition 'entry_len<token_len' is always false
         */
        if (entry_len < token_len || entry_len < suffix_len) {
            free(result);
            free(content);
            *out_len = 0;
            return NULL;
        }
        if (entry_len == SIZE_MAX) {
            free(result);
            free(content);
            *out_len = 0;
            return NULL;
        }

        if (length > SIZE_MAX - entry_len - 1) {
            free(result);
            free(content);
            *out_len = 0;
            return NULL;
        }

        while (length + entry_len + 1 > capacity) {
            size_t new_capacity;
            if (capacity > SIZE_MAX / 2) {
                new_capacity = length + entry_len + 1;
                if (new_capacity <= capacity) {
                    free(result);
                    free(content);
                    *out_len = 0;
                    return NULL;
                }
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < capacity) {
                    new_capacity = length + entry_len + 1;
                }
            }
            char *temp = (char *)realloc(result, new_capacity);
            if (!temp) {
                free(result);
                free(content);
                *out_len = 0;
                return NULL;
            }
            result = temp;
            capacity = new_capacity;
        }

        if (!first) {
            result[length++] = ' ';
        }

        if (token_len > 0) {
            if (length > SIZE_MAX - token_len) {
                free(result);
                free(content);
                *out_len = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             *  Assuming that condition 'length+token_len>capacity' is not redundant
             */
            while (length + token_len > capacity) {
                size_t new_capacity;
                if (capacity > SIZE_MAX / 2) {
                    /* Possible weaknesses found:
                     *  new_capacity is assigned 'length+token_len' here.
                     */
                    new_capacity = length + token_len;
                    /* Possible weaknesses found:
                     *  Condition 'new_capacity<=capacity' is always true
                     *  Condition 'new_capacity<=capacity' is always true [knownConditionTrueFalse]
                     */
                    if (new_capacity <= capacity) {
                        free(result);
                        free(content);
                        *out_len = 0;
                        return NULL;
                    }
                } else {
                    new_capacity = capacity * 2;
                    if (new_capacity < capacity) {
                        new_capacity = length + token_len;
                    }
                }
                char *temp = (char *)realloc(result, new_capacity);
                if (!temp) {
                    free(result);
                    free(content);
                    *out_len = 0;
                    return NULL;
                }
                result = temp;
                capacity = new_capacity;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + length, token, token_len);
            length += token_len;
        }

        if (suffix_len > 0) {
            if (length > SIZE_MAX - suffix_len) {
                free(result);
                free(content);
                *out_len = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             *  Assuming that condition 'length+suffix_len>capacity' is not redundant
             */
            while (length + suffix_len > capacity) {
                size_t new_capacity;
                if (capacity > SIZE_MAX / 2) {
                    /* Possible weaknesses found:
                     *  new_capacity is assigned 'length+suffix_len' here.
                     */
                    new_capacity = length + suffix_len;
                    /* Possible weaknesses found:
                     *  Condition 'new_capacity<=capacity' is always true
                     *  Condition 'new_capacity<=capacity' is always true [knownConditionTrueFalse]
                     */
                    if (new_capacity <= capacity) {
                        free(result);
                        free(content);
                        *out_len = 0;
                        return NULL;
                    }
                } else {
                    new_capacity = capacity * 2;
                    if (new_capacity < capacity) {
                        new_capacity = length + suffix_len;
                    }
                }
                char *temp = (char *)realloc(result, new_capacity);
                if (!temp) {
                    free(result);
                    free(content);
                    *out_len = 0;
                    return NULL;
                }
                result = temp;
                capacity = new_capacity;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + length, suffix, suffix_len);
            length += suffix_len;
        }

        result[length] = '\0';
        first = 0;

        token = strtok_r(NULL, ",", &saveptr);
    }

    free(content);
    *out_len = (int)length;
    return result;
}

int main(void) {
    const char *tuple_str = "(apple, banana, cherry)";
    const char *suffix = "!";
    int len = 0;
    char *list = convert_tuple_to_list(tuple_str, suffix, &len);

    if (list) {
        printf("[%s]\n", list);
        printf("Length: %d\n", len);
        free(list);
    } else {
        printf("Invalid input or memory allocation failed.\n");
    }

    return 0;
}