#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 1024

void reverse_string(char *str)
{
    size_t len;
    size_t i;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, MAX_STRING_LEN);
    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
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
    }

    for (i = 0; i < count; i++) {
        reverse_string(list[i]);
    }

    return 0;
}

int main(void)
{
    const char *strings[] = {"hello", "world", "programming", "language", "reverse"};
    size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t i;
    size_t j;
    char **list;

    list = malloc(count * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        list[i] = NULL;
    }

    for (i = 0; i < count; i++) {
        size_t src_len = strnlen(strings[i], MAX_STRING_LEN);
        size_t len = src_len + 1;
        int written;

        list[i] = malloc(len);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < count; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }

        written = snprintf(list[i], len, "%s", strings[i]);
        if (written < 0 || (size_t)written >= len) {
            fprintf(stderr, "String copy failed\n");
            for (j = 0; j < count; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
    }

    printf("Original list:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    if (reverse_string_list(list, count) != 0) {
        fprintf(stderr, "Failed to reverse string list\n");
        for (i = 0; i < count; i++) {
            free(list[i]);
        }
        free(list);
        return EXIT_FAILURE;
    }

    printf("Reversed list:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}