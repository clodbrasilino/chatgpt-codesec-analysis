#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int reverse_string(char *str)
{
    size_t left;
    size_t right;
    char temp;

    if (str == NULL) {
        return -1;
    }

    left = 0;
    right = strlen(str);

    if (right == 0) {
        return 0;
    }

    right--;

    while (left < right) {
        temp = str[left];
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
        size_t len = strlen(source[i]);

        list[i] = malloc(len + 1);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_string_list(list, count);
            return EXIT_FAILURE;
        }

        memcpy(list[i], source[i], len + 1);
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