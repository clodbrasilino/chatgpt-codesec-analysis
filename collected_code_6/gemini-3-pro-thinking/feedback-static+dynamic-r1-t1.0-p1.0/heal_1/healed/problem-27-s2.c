#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void remove_digits(char **strings, size_t count);

void remove_digits(char **strings, size_t count) {
    if (strings == NULL || count == 0) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t write_idx = 0;
        for (size_t read_idx = 0; strings[i][read_idx] != '\0'; read_idx++) {
            if (!isdigit((unsigned char)strings[i][read_idx])) {
                strings[i][write_idx++] = strings[i][read_idx];
            }
        }
        strings[i][write_idx] = '\0';
    }
}

int main(void) {
    const char *initial_strings[] = {
        "H3ll0 W0rld1",
        "4b5c6d",
        "N0 D1g1t5 H3r3",
        "12345"
    };
    
    size_t count = sizeof(initial_strings) / sizeof(initial_strings[0]);
    
    char **strings = malloc(count * sizeof(char *));
    if (strings == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        int len = snprintf(NULL, 0, "%s", initial_strings[i]);
        if (len < 0) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return EXIT_FAILURE;
        }

        strings[i] = malloc((size_t)len + 1);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return EXIT_FAILURE;
        }

        snprintf(strings[i], (size_t)len + 1, "%s", initial_strings[i]);
    }

    remove_digits(strings, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);

    return EXIT_SUCCESS;
}