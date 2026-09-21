#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

static int reverse_string(char *str)
{
    size_t len;
    size_t i;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, MAX_STRING_LENGTH);

    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }

    return 0;
}

static int reverse_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (reverse_string(list[i]) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const char *words[] = {"hello", "world", "reverse", "strings", "example"};
    size_t count = sizeof(words) / sizeof(words[0]);
    char **list;
    size_t i;
    int status = EXIT_SUCCESS;

    list = malloc(count * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        size_t len = strnlen(words[i], MAX_STRING_LENGTH) + 1;
        int written;

        list[i] = malloc(len);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            while (i > 0) {
                i--;
                free(list[i]);
            }
            free(list);
            return EXIT_FAILURE;
        }

        written = snprintf(list[i], len, "%s", words[i]);
        if (written < 0 || (size_t)written >= len) {
            fprintf(stderr, "String copy failed\n");
            free(list[i]);
            while (i > 0) {
                i--;
                free(list[i]);
            }
            free(list);
            return EXIT_FAILURE;
        }
    }

    printf("Original strings:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    if (reverse_string_list(list, count) != 0) {
        fprintf(stderr, "Failed to reverse string list\n");
        status = EXIT_FAILURE;
    } else {
        printf("Reversed strings:\n");
        for (i = 0; i < count; i++) {
            printf("%s\n", list[i]);
        }
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return status;
}