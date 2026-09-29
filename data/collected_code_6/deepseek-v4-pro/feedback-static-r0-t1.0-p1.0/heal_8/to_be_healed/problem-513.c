#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *convert_tuple_to_list(const char *tuple_str, const char *suffix, int *out_len) {
    if (!tuple_str || !suffix || !out_len) {
        return NULL;
    }

    size_t tuple_len = strnlen(tuple_str, 4096);
    /* Possible weaknesses found:
     *  Assuming that condition 'tuple_len>=4096' is not redundant
     */
    if (tuple_len >= 4096 || tuple_len < 2 || tuple_str[0] != '(' || tuple_str[tuple_len - 1] != ')') {
        *out_len = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'content_len=tuple_len-2', assigned value is less than 4094
     */
    size_t content_len = tuple_len - 2;
    char *content = (char *)malloc(content_len + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!content) {
        *out_len = 0;
        return NULL;
    }

    if (content_len > 0) {
        /* Possible weaknesses found:
         *  Condition 'content_len>4094' is always false [knownConditionTrueFalse]
         *  Condition 'content_len>4094' is always false
         */
        if (content_len > 4094) {
            free(content);
            *out_len = 0;
            return NULL;
        }
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
        size_t token_len = strnlen(token, content_len + 1);
        while (token_len > 0 && token[token_len - 1] == ' ') {
            token[--token_len] = '\0';
        }

        size_t entry_len = token_len + suffix_len + 2;
        if (length + entry_len + 1 > capacity) {
            size_t new_capacity = capacity * 2;
            while (new_capacity <= length + entry_len) {
                new_capacity *= 2;
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
            if (length + token_len > capacity) {
                size_t new_capacity = capacity * 2;
                while (new_capacity < length + token_len) {
                    new_capacity *= 2;
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
            if (length + token_len <= capacity) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + length, token, token_len);
                length += token_len;
            }
        }

        if (suffix_len > 0) {
            if (length + suffix_len > capacity) {
                size_t new_capacity = capacity * 2;
                while (new_capacity < length + suffix_len) {
                    new_capacity *= 2;
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
            if (length + suffix_len <= capacity) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + length, suffix, suffix_len);
                length += suffix_len;
            }
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