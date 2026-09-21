#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 4096

char *remove_non_alnum(char *str, size_t max_len);

char *remove_non_alnum(char *str, size_t max_len)
{
    size_t read;
    size_t write;
    size_t len;

    if (str == NULL || max_len == 0) {
        return NULL;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        return NULL;
    }

    write = 0;
    for (read = 0; read < len && read < max_len; read++) {
        if (isalnum((unsigned char)str[read])) {
            if (write >= max_len - 1) {
                return NULL;
            }
            str[write] = str[read];
            write++;
        }
    }

    if (write >= max_len) {
        return NULL;
    }
    str[write] = '\0';

    return str;
}

int main(void)
{
    char input[] = "Hello, World! 123 #$%^ test_case-42";
    char *result;

    if (sizeof(input) > MAX_INPUT_LEN) {
        if (fprintf(stderr, "Error: input exceeds maximum length\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    result = remove_non_alnum(input, sizeof(input));
    if (result == NULL) {
        if (fprintf(stderr, "Error: invalid input string\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Result: %s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}