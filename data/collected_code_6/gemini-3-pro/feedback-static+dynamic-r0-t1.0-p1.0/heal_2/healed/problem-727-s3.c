#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 8192

void filter_alphanumeric(const char *input, char **output) {
    if (input == NULL || output == NULL) {
        return;
    }

    size_t len = strnlen(input, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN) {
        *output = NULL;
        return;
    }

    *output = (char *)malloc(len + 1);
    if (*output == NULL) {
        return;
    }

    const char *p = input;
    char *out_p = *output;

    while (*p != '\0' && (size_t)(p - input) < len) {
        if (isalnum((unsigned char)*p)) {
            *out_p = *p;
            out_p++;
        }
        p++;
    }
    *out_p = '\0';
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;

    filter_alphanumeric(input, &output);

    if (output != NULL) {
        printf("Original: %s\n", input);
        printf("Filtered: %s\n", output);
        free(output);
    } else {
        printf("Error processing string.\n");
    }

    return 0;
}