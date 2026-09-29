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
                size_t copy_len = (size_t)len < result_size - 1 ? (size_t)len : result_size - 1;
                memcpy(result, start, copy_len);
                result[copy_len] = '\0';
                found = 1;
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
    char output[256] = {0};

    int length = find_first_max_even_word(input, output, sizeof(output));

    if (length > 0) {
        printf("%s\n", output);
    } else {
        printf("No even length word found\n");
    }

    return 0;
}