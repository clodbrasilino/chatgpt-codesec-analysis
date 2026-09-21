#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 4096

char *duplicate_string(const char *src) {
    if (src == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(src, MAX_STR_LEN);
    char *dst = malloc(len + 1);
    if (dst != NULL) {
        memcpy(dst, src, len);
        dst[len] = '\0';
    }
    return dst;
}

int remove_duplicates(const char **input_list, size_t input_count, char ***output_list, size_t *output_count) {
    if (input_list == NULL || output_list == NULL || output_count == NULL) {
        return -1;
    }

    *output_list = NULL;
    *output_count = 0;

    if (input_count == 0) {
        return 0;
    }

    char **unique_list = malloc(input_count * sizeof(char *));
    if (unique_list == NULL) {
        return -1;
    }

    size_t count = 0;
    for (size_t i = 0; i < input_count; i++) {
        if (input_list[i] == NULL) {
            continue;
        }

        bool is_duplicate = false;
        for (size_t j = 0; j < count; j++) {
            if (strncmp(input_list[i], unique_list[j], MAX_STR_LEN) == 0) {
                is_duplicate = true;
                break;
            }
        }

        if (!is_duplicate) {
            char *new_string = duplicate_string(input_list[i]);
            if (new_string == NULL) {
                for (size_t k = 0; k < count; k++) {
                    free(unique_list[k]);
                }
                free(unique_list);
                return -1;
            }
            unique_list[count++] = new_string;
        }
    }

    if (count > 0 && count < input_count) {
        char **shrunk_list = realloc(unique_list, count * sizeof(char *));
        if (shrunk_list != NULL) {
            unique_list = shrunk_list;
        }
    } else if (count == 0) {
        free(unique_list);
        unique_list = NULL;
    }

    *output_list = unique_list;
    *output_count = count;
    return 0;
}

int main(void) {
    const char *words[] = {
        "apple",
        "banana",
        "apple",
        "orange",
        "banana",
        "grape"
    };
    size_t input_count = sizeof(words) / sizeof(words[0]);
    
    char **unique_words = NULL;
    size_t output_count = 0;

    int status = remove_duplicates((const char **)words, input_count, &unique_words, &output_count);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < output_count; i++) {
        printf("%s\n", unique_words[i]);
    }

    for (size_t i = 0; i < output_count; i++) {
        free(unique_words[i]);
    }
    free(unique_words);

    return EXIT_SUCCESS;
}