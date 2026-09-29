#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

static void reverse_string(char *str)
{
    size_t len;
    size_t i;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, MAX_STRING_LEN);
    if (len < 2) {
        return;
    }

    for (i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

static int reverse_string_list(char **list, size_t count)
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

static void free_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

static char *duplicate_string(const char *src)
{
    size_t len;
    size_t dst_size;
    size_t i;
    char *dst;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }

    dst_size = len + 1;
    dst = malloc(dst_size);
    if (dst == NULL) {
        return NULL;
    }

    for (i = 0; i < len && i < dst_size - 1; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';

    return dst;
}

int main(void)
{
    const char *source[] = { "hello", "world", "example", "c" };
    size_t count = sizeof(source) / sizeof(source[0]);
    char **list;
    size_t i;

    list = calloc(count, sizeof(char *));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        list[i] = duplicate_string(source[i]);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_string_list(list, i);
            return EXIT_FAILURE;
        }
    }

    if (reverse_string_list(list, count) != 0) {
        fprintf(stderr, "Failed to reverse string list\n");
        free_string_list(list, count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", list[i]) < 0) {
            free_string_list(list, count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(list, count);
    return EXIT_SUCCESS;
}