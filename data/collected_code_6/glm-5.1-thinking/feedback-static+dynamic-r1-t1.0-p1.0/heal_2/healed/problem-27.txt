#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int remove_digits_from_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t write_idx = 0;

        for (size_t read_idx = 0; strings[i][read_idx] != '\0'; read_idx++) {
            if (!isdigit((unsigned char)strings[i][read_idx])) {
                strings[i][write_idx] = strings[i][read_idx];
                write_idx++;
            }
        }
        strings[i][write_idx] = '\0';
    }

    return 0;
}

int main(void) {
    const char *original[] = {
        "Hello123 World456",
        "C0d1ng2 is3 f4n5",
        "NoDigitsHere",
        "12345",
        ""
    };

    size_t count = sizeof(original) / sizeof(original[0]);
    char **strings = malloc(count * sizeof(char *));
    if (strings == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        size_t len = snprintf(NULL, 0, "%s", original[i]);
        strings[i] = malloc(len + 1);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return EXIT_FAILURE;
        }
        snprintf(strings[i], len + 1, "%s", original[i]);
    }

    if (remove_digits_from_strings(strings, count) != 0) {
        for (size_t i = 0; i < count; i++) {
            free(strings[i]);
        }
        free(strings);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);

    return EXIT_SUCCESS;
}