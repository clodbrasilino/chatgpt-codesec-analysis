#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LEN 4096

size_t safe_strnlen(const char *str, size_t maxlen);
void remove_digits(char **strings, size_t count);

size_t safe_strnlen(const char *str, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && str[len] != '\0') {
        len++;
    }
    return len;
}

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
        size_t len = safe_strnlen(initial_strings[i], MAX_STRING_LEN);
        
        strings[i] = malloc(len + 1);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return EXIT_FAILURE;
        }
        
        snprintf(strings[i], len + 1, "%s", initial_strings[i]);
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