#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

static int reverse_string(char *str)
{
    size_t left;
    size_t right;

    if (str == NULL) {
        return -1;
    }

    left = 0;
    right = strnlen(str, MAX_STRING_LENGTH);

    if (right == MAX_STRING_LENGTH) {
        return -1;
    }

    if (right == 0) {
        return 0;
    }

    right--;

    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
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

static void free_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
        list[i] = NULL;
    }

    free(list);
}

static char *duplicate_string(const char *source)
{
    size_t len;
    size_t alloc_size;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    len = strnlen(source, MAX_STRING_LENGTH);

    if (len >= MAX_STRING_LENGTH) {
        return NULL;
    }

    if (len > SIZE_MAX - 1) {
        return NULL;
    }

    alloc_size = len + 1;

    copy = malloc(alloc_size);
    if (copy == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, len);
    }

    copy[len] = '\0';

    return copy;
}

int main(void)
{
    const char *source[] = { "hello", "world", "example", "" };
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
            fprintf(stderr, "Failed to duplicate string\n");
            free_string_list(list, count);
            return EXIT_FAILURE;
        }
    }

    if (reverse_string_list(list, count) != 0) {
        fprintf(stderr, "Failed to reverse string list\n");
        free_string_list(list, count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    free_string_list(list, count);

    return EXIT_SUCCESS;
}