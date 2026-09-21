#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 1024

static void reverse_string(char *str)
{
    size_t len;
    size_t i;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, MAX_STRING_LEN + 1);
    if (len < 2 || len > MAX_STRING_LEN) {
        return;
    }

    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

static int reverse_strings(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            return -1;
        }
        reverse_string(strings[i]);
    }

    return 0;
}

int main(void)
{
    const char *input[] = {"hello", "world", "programming", "reverse"};
    size_t count = sizeof(input) / sizeof(input[0]);
    char **strings;
    size_t i;
    size_t len;
    int status = EXIT_SUCCESS;

    strings = malloc(count * sizeof(*strings));
    if (strings == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        len = strnlen(input[i], MAX_STRING_LEN + 1);
        if (len > MAX_STRING_LEN) {
            fprintf(stderr, "Input string too long or not null-terminated\n");
            while (i > 0) {
                i--;
                free(strings[i]);
            }
            free(strings);
            return EXIT_FAILURE;
        }
        strings[i] = malloc(len + 1);
        if (strings[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            while (i > 0) {
                i--;
                free(strings[i]);
            }
            free(strings);
            return EXIT_FAILURE;
        }
        memcpy(strings[i], input[i], len + 1);
    }

    if (reverse_strings(strings, count) != 0) {
        fprintf(stderr, "Failed to reverse strings\n");
        status = EXIT_FAILURE;
    } else {
        for (i = 0; i < count; i++) {
            if (printf("%s\n", strings[i]) < 0) {
                fprintf(stderr, "Output error\n");
                status = EXIT_FAILURE;
                break;
            }
        }
    }

    for (i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);

    return status;
}