#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

void reverse_string(const char* str, size_t len, char* rev) {
    for (size_t i = 0; i < len; ++i) {
        rev[i] = str[len - 1 - i];
    }
    rev[len] = '\0';
}

int count_reverse_pairs(char** str_list, size_t list_size) {
    if (str_list == NULL || list_size == 0) {
        return 0;
    }

    int count = 0;
    size_t i, j;

    for (i = 0; i < list_size; ++i) {
        if (str_list[i] == NULL) {
            continue;
        }

        size_t len = strnlen(str_list[i], MAX_STRING_LEN);
        char* rev = (char*)malloc(len + 1);
        if (rev == NULL) {
            return -1; 
        }

        reverse_string(str_list[i], len, rev);

        for (j = i + 1; j < list_size; ++j) {
            if (str_list[j] != NULL && strncmp(rev, str_list[j], MAX_STRING_LEN) == 0) {
                count++;
            }
        }
        free(rev);
    }

    return count;
}

int main(void) {
    char* list[] = {
        "hello",
        "world",
        "olleh",
        "dlrow",
        "test",
        "tset",
        "abc"
    };
    size_t size = sizeof(list) / sizeof(list[0]);

    int result = count_reverse_pairs(list, size);

    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Number of reverse pairs: %d\n", result);

    return EXIT_SUCCESS;
}