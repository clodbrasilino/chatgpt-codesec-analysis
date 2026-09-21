#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_odd_index_chars(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }

    size_t len = strnlen(str, max_len);
    size_t i, j = 0;

    for (i = 0; i < len; i++) {
        if (i % 2 == 0) {
            if (j < max_len - 1) {
                str[j++] = str[i];
            }
        }
    }
    str[j] = '\0';
}

int main(void) {
    char str[100];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strnlen(str, sizeof(str));
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    remove_odd_index_chars(str, sizeof(str));

    printf("Result: %s\n", str);

    return EXIT_SUCCESS;
}