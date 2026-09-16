#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str)
{
    size_t len;
    size_t i;
    char temp;

    if (str == NULL) {
        return;
    }

    len = strlen(str);
    if (len < 2) {
        return;
    }

    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int reverse_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (list[i] == NULL) {
            return -1;
        }
        reverse_string(list[i]);
    }

    return 0;
}

int main(void)
{
    const char *source[] = { "hello", "world", "example", "C" };
    size_t count = sizeof(source) / sizeof(source[0]);
    char **list;
    size_t i;
    size_t j;

    list = malloc(count * sizeof(char *));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        size_t len = strlen(source[i]);
        list[i] = malloc(len + 1);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
        memcpy(list[i], source[i], len + 1);
    }

    if (reverse_string_list(list, count) != 0) {
        fprintf(stderr, "Failed to reverse string list\n");
        for (i = 0; i < count; i++) {
            free(list[i]);
        }
        free(list);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", list[i]) < 0) {
            fprintf(stderr, "Output error\n");
            for (j = 0; j < count; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}