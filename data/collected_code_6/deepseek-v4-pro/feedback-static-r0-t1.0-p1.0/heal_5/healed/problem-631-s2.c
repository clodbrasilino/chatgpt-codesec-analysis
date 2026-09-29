#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_whitespace_underscore(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        if (len >= SIZE_MAX - 1) {
            return NULL;
        }
        len++;
    }

    size_t result_size = len + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t src_idx = 0, dst_idx = 0;

    while (src_idx < len) {
        char current = input[src_idx];
        
        if (current == ' ') {
            if (dst_idx >= result_size - 1) {
                free(result);
                return NULL;
            }
            result[dst_idx++] = '_';
            src_idx++;
        } else if (current == '_') {
            if (dst_idx >= result_size - 1) {
                free(result);
                return NULL;
            }
            result[dst_idx++] = ' ';
            src_idx++;
        } else {
            size_t start = src_idx;
            while (src_idx < len && input[src_idx] != ' ' && input[src_idx] != '_') {
                src_idx++;
            }
            size_t copy_len = src_idx - start;
            if (dst_idx + copy_len >= result_size) {
                free(result);
                return NULL;
            }
            if (copy_len > 0) {
                size_t remaining = result_size - dst_idx;
                if (copy_len > remaining) {
                    free(result);
                    return NULL;
                }
                memcpy(result + dst_idx, input + start, copy_len);
                dst_idx += copy_len;
            }
        }
    }

    if (dst_idx >= result_size) {
        free(result);
        return NULL;
    }
    result[dst_idx] = '\0';
    return result;
}

int main(void) {
    const char *test1 = "hello world_this_is_a_test";
    const char *test2 = "no_spaces_here";
    const char *test3 = "   ___   ";
    const char *test4 = "";
    const char *test5 = NULL;

    char *res1 = replace_whitespace_underscore(test1);
    char *res2 = replace_whitespace_underscore(test2);
    char *res3 = replace_whitespace_underscore(test3);
    char *res4 = replace_whitespace_underscore(test4);
    char *res5 = replace_whitespace_underscore(test5);

    printf("Test 1: %s -> %s\n", test1 ? test1 : "(null)", res1 ? res1 : "(null)");
    printf("Test 2: %s -> %s\n", test2 ? test2 : "(null)", res2 ? res2 : "(null)");
    printf("Test 3: %s -> %s\n", test3 ? test3 : "(null)", res3 ? res3 : "(null)");
    printf("Test 4: %s -> %s\n", test4 ? test4 : "(null)", res4 ? res4 : "(null)");
    printf("Test 5: %s -> %s\n", test5 ? test5 : "(null)", res5 ? res5 : "(null)");

    free(res1);
    free(res2);
    free(res3);
    free(res4);
    free(res5);

    return 0;
}