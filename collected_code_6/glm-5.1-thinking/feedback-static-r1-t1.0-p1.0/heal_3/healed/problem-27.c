#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int remove_digits_from_strings(char **strings, size_t count, const size_t *buf_sizes) {
    if (strings == NULL || buf_sizes == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL || buf_sizes[i] == 0) {
            continue;
        }

        char *str = strings[i];
        size_t max_len = buf_sizes[i];
        size_t write_idx = 0;

        for (size_t j = 0; j < max_len && str[j] != '\0'; j++) {
            if (!isdigit((unsigned char)str[j])) {
                if (write_idx < max_len) {
                    str[write_idx++] = str[j];
                }
            }
        }
        
        if (write_idx < max_len) {
            str[write_idx] = '\0';
        } else {
            str[max_len - 1] = '\0';
        }
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
    size_t *buf_sizes = malloc(count * sizeof(size_t));

    if (strings == NULL || buf_sizes == NULL) {
        free(strings);
        free(buf_sizes);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        size_t len = strlen(original[i]);
        buf_sizes[i] = len + 1;
        strings[i] = malloc(buf_sizes[i]);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            free(buf_sizes);
            return EXIT_FAILURE;
        }
        snprintf(strings[i], buf_sizes[i], "%s", original[i]);
    }

    if (remove_digits_from_strings(strings, count, buf_sizes) != 0) {
        for (size_t i = 0; i < count; i++) {
            free(strings[i]);
        }
        free(strings);
        free(buf_sizes);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
    free(buf_sizes);

    return EXIT_SUCCESS;
}