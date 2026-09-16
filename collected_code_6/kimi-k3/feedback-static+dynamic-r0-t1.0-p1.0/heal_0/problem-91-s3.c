#include <stdio.h>
#include <string.h>

int contains_substring(const char *const *strings, size_t count, const char *substring) {
    size_t i;

    if (strings == NULL || substring == NULL) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] != NULL && strstr(strings[i], substring) != NULL) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *values[] = {
        "hello world",
        "test string",
        "substring example",
        "another value"
    };
    const char *substring = "string";
    size_t count = sizeof(values) / sizeof(values[0]);

    if (contains_substring(values, count, substring)) {
        printf("Substring found.\n");
    } else {
        printf("Substring not found.\n");
    }

    return 0;
}