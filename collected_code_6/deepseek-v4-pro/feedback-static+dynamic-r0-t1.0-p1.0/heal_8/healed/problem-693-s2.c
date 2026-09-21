#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t alloc_size = 64;
    char *result = (char *)malloc(alloc_size);
    if (result == NULL) {
        return NULL;
    }

    size_t result_pos = 0;
    size_t current_pos = 0;
    int in_space = 0;

    while (input[current_pos] != '\0') {
        char c = input[current_pos];

        if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f') {
            if (!in_space && result_pos > 0) {
                if (result_pos + 1 >= alloc_size) {
                    size_t new_alloc_size = alloc_size * 2;
                    if (new_alloc_size < alloc_size || new_alloc_size > SIZE_MAX - 1) {
                        free(result);
                        return NULL;
                    }
                    char *temp = (char *)realloc(result, new_alloc_size);
                    if (temp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    alloc_size = new_alloc_size;
                }
                result[result_pos] = ' ';
                result_pos++;
                in_space = 1;
            }
            current_pos++;
        } else {
            if (result_pos + 1 >= alloc_size) {
                size_t new_alloc_size = alloc_size * 2;
                if (new_alloc_size < alloc_size || new_alloc_size > SIZE_MAX - 1) {
                    free(result);
                    return NULL;
                }
                char *temp = (char *)realloc(result, new_alloc_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                alloc_size = new_alloc_size;
            }
            result[result_pos] = c;
            result_pos++;
            in_space = 0;
            current_pos++;
        }
    }

    if (result_pos > 0 && result[result_pos - 1] == ' ') {
        result_pos--;
    }

    if (result_pos + 1 >= alloc_size) {
        size_t new_alloc_size = result_pos + 1;
        if (new_alloc_size > SIZE_MAX - 1) {
            free(result);
            return NULL;
        }
        char *temp = (char *)realloc(result, new_alloc_size);
        if (temp == NULL) {
            free(result);
            return NULL;
        }
        result = temp;
    }
    result[result_pos] = '\0';

    return result;
}

int main(void) {
    const char *tests[] = {
        "This   is    a test   string.",
        "  Leading   and   trailing   spaces  ",
        "No multiple spaces here.",
        "   ",
        "",
        "Tab\t\tand   spaces\n\nmixed"
    };
    
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        char *result = remove_multiple_spaces(tests[i]);
        if (result != NULL) {
            printf("Test%zu: '%s' -> '%s'\n", i + 1, tests[i], result);
            free(result);
        } else {
            printf("Test%zu: '%s' -> Error processing string\n", i + 1, tests[i]);
        }
    }

    return 0;
}