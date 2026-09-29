#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

void reverse_string(char *str)
{
    size_t len;
    size_t i;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, MAX_STRING_LENGTH);
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

static char *duplicate_string(const char *src)
{
    size_t len;
    size_t dest_size;
    char *dest;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LENGTH);
    if (len >= MAX_STRING_LENGTH) {
        return NULL;
    }

    dest_size = len + 1;
    dest = malloc(dest_size);
    if (dest == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, len);
    dest[len] = '\0';

    return dest;
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
        list[i] = duplicate_string(source[i]);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(list, count);
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