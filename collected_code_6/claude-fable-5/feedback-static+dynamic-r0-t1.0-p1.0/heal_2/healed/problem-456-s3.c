#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

void reverse_string(char *str)
{
    size_t len;
    size_t i;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, MAX_STR_LEN);
    if (len < 2) {
        return;
    }

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
        reverse_string(list[i]);
    }

    return 0;
}

static void free_list(char **list, size_t count)
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

static int copy_string(char *dest, size_t dest_size, const char *src, size_t src_len)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (src_len >= dest_size) {
        return -1;
    }
    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return 0;
}

int main(void)
{
    const char *source[] = { "hello", "world", "example", "C" };
    size_t count = sizeof(source) / sizeof(source[0]);
    char **list;
    size_t i;

    list = calloc(count, sizeof(char *));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        size_t len = strnlen(source[i], MAX_STR_LEN);
        size_t buf_size = len + 1;

        list[i] = malloc(buf_size);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(list, i);
            return EXIT_FAILURE;
        }

        if (copy_string(list[i], buf_size, source[i], len) != 0) {
            fprintf(stderr, "String copy failed\n");
            free_list(list, i + 1);
            return EXIT_FAILURE;
        }
    }

    if (reverse_string_list(list, count) != 0) {
        fprintf(stderr, "Failed to reverse string list\n");
        free_list(list, count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", list[i]) < 0) {
            fprintf(stderr, "Output error\n");
            free_list(list, count);
            return EXIT_FAILURE;
        }
    }

    free_list(list, count);

    return EXIT_SUCCESS;
}