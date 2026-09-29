#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>

char **split_at_uppercase(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[2];
    char **result = NULL;
    size_t capacity = 0;
    size_t index = 0;
    const char *cursor = input;
    int status;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    status = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    capacity = 16;
    result = (char **)malloc(sizeof(char *) * capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 2, matches, 0);
        if (status == REG_NOMATCH) {
            size_t len = strnlen(cursor, SIZE_MAX - (size_t)(cursor - input));
            if (len > 0) {
                if (index >= capacity) {
                    size_t new_capacity = capacity * 2;
                    char **temp = (char **)realloc(result, sizeof(char *) * new_capacity);
                    if (temp == NULL) {
                        for (size_t i = 0; i < index; i++) {
                            free(result[i]);
                        }
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                    capacity = new_capacity;
                }
                result[index] = (char *)malloc(len + 1);
                if (result[index] == NULL) {
                    for (size_t i = 0; i < index; i++) {
                        free(result[i]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                if (len > 0) {
                    memcpy(result[index], cursor, len);
                }
                result[index][len] = '\0';
                index++;
            }
            break;
        } else if (status == 0) {
            size_t split_pos = (size_t)matches[0].rm_so;
            if (split_pos > 0) {
                if (index >= capacity) {
                    size_t new_capacity = capacity * 2;
                    char **temp = (char **)realloc(result, sizeof(char *) * new_capacity);
                    if (temp == NULL) {
                        for (size_t i = 0; i < index; i++) {
                            free(result[i]);
                        }
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                    capacity = new_capacity;
                }
                result[index] = (char *)malloc(split_pos + 1);
                if (result[index] == NULL) {
                    for (size_t i = 0; i < index; i++) {
                        free(result[i]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                if (split_pos > 0) {
                    memcpy(result[index], cursor, split_pos);
                }
                result[index][split_pos] = '\0';
                index++;
                cursor += split_pos;
            } else {
                cursor += matches[0].rm_eo;
            }
        } else {
            for (size_t i = 0; i < index; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    if (index == 0) {
        free(result);
        regfree(&regex);
        return NULL;
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