#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

static int reverse_string(char *str)
{
    size_t left;
    size_t right;

    if (str == NULL) {
        return -1;
    }

    left = 0;
    right = strnlen(str, MAX_STRING_LEN);

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
    size_t dest_size;
    char *dest;

    if (source == NULL) {
        return NULL;
    }

    len = strnlen(source, MAX_STRING_LEN);

    if (len >= MAX_STRING_LEN) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  dest_size is assigned 'len+1' here.
     */
    dest_size = len + 1;

    dest = malloc(dest_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (dest == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         *  Condition 'len>=dest_size' is always false
         *  Condition 'len>=dest_size' is always false [knownConditionTrueFalse]
         */
        if (len >= dest_size) {
            free(dest);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, source, len);
    }

    dest[len] = '\0';

    return dest;
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