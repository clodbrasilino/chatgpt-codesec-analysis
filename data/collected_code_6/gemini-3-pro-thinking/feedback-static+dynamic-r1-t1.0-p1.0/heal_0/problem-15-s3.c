#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_at_lowercase(const char *str, size_t *out_count) {
    if (str == NULL || out_count == NULL) {
        return NULL;
    }

    size_t count = 1;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (islower((unsigned char)str[i])) {
            count++;
        }
    }

    char **result = calloc(count, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t current_str_idx = 0;
    const char *start = str;

    for (size_t i = 0; ; i++) {
        if (str[i] == '\0' || islower((unsigned char)str[i])) {
            size_t len = (size_t)(&str[i] - start);
            
            result[current_str_idx] = malloc(len + 1);
            if (result[current_str_idx] == NULL) {
                for (size_t j = 0; j < current_str_idx; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            if (len > 0) {
                memcpy(result[current_str_idx], start, len);
            }
            result[current_str_idx][len] = '\0';
            current_str_idx++;

            if (str[i] == '\0') {
                break;
            }
            start = &str[i + 1];
        }
    }

    *out_count = count;
    return result;
}

void free_split_result(char **result, size_t count) {
    if (result == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *test_string = "HELLOwORLDxTESTaCWE";
    size_t count = 0;

    char **substrings = split_at_lowercase(test_string, &count);
    if (substrings != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("[%zu]: %s\n", i, substrings[i]);
        }
        free_split_result(substrings, count);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}