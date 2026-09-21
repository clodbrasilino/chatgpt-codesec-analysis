#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t len = 0;

    if (str == NULL) {
        return 0;
    }

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    return len;
}

static void bounded_copy(char *dst, const char *src, size_t dst_size)
{
    size_t i;

    if (dst == NULL || src == NULL || dst_size == 0) {
        return;
    }

    for (i = 0; i < dst_size - 1 && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
}

void reverse_string(char *str)
{
    size_t len;
    size_t i;

    if (str == NULL) {
        return;
    }

    len = bounded_strlen(str, MAX_STRING_LENGTH);
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
        size_t len = bounded_strlen(strings[i], MAX_STRING_LENGTH) + 1;
        list[i] = malloc(len);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < count; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
        bounded_copy(list[i], strings[i], len);
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