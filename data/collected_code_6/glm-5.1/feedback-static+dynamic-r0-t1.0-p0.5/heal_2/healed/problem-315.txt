#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_first_max_even_word(const char *str, char *result, size_t result_size) {
    if (str == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    int max_len = 0;
    int found = 0;
    const char *p = str;

    while (*p != '\0') {
        while (*p == ' ') {
            p++;
        }

        if (*p == '\0') {
            break;
        }

        const char *start = p;
        while (*p != '\0' && *p != ' ') {
            p++;
        }

        int len = (int)(p - start);

        if (len % 2 == 0) {
            if (len > max_len) {
                max_len = len;
                if ((size_t)len < result_size) {
                    snprintf(result, result_size, "%.*s", len, start);
                    found = 1;
                } else {
                    snprintf(result, result_size, "%.*s", (int)(result_size - 1), start);
                    found = 1;
                }
            }
        }
    }

    if (found) {
        return max_len;
    }

    return 0;
}

int main() {
    const char input[] = "This is a test string containing several even length words";
    size_t output_size = 256;
    char *output = (char *)malloc(output_size * sizeof(char));
    if (output == NULL) {
        return 1;
    }

    int length = find_first_max_even_word(input, output, output_size);

    if (length > 0) {
        printf("%s\n", output);
    } else {
        printf("No even length word found\n");
    }

    free(output);
    return 0;
}