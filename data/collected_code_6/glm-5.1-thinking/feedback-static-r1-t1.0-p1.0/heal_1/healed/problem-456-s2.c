#include <stdio.h>
#include <stdlib.h>

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        char *start = strings[i];
        char *end = strings[i];
        while (*end != '\0') {
            end++;
        }
        if (end > start) {
            end--;
        }
        while (start < end) {
            char temp = *start;
            *start = *end;
            *end = temp;
            start++;
            end--;
        }
    }
}

int main(void) {
    const char *original[] = {
        "hello",
        "world",
        "C",
        "programming"
    };
    size_t count = sizeof(original) / sizeof(original[0]);

    char **strings = malloc(count * sizeof(char *));
    if (strings == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        int len = snprintf(NULL, 0, "%s", original[i]);
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
        snprintf(strings[i], (size_t)len + 1, "%s", original[i]);
    }

    reverse_strings(strings, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);

    return EXIT_SUCCESS;
}