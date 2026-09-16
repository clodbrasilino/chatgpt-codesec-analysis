#include <stdio.h>
#include <stdlib.h>

typedef void (*MapFunc)(const char *);

void map(char **array, size_t size, MapFunc func) {
    if (array == NULL || func == NULL) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        if (array[i] != NULL) {
            func(array[i]);
        }
    }
}

void print_string(const char *str) {
    if (str == NULL) {
        return;
    }
    printf("%s\n", str);
}

int main(void) {
    char *strings[] = {
        "apple",
        "banana",
        "cherry"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);

    map(strings, count, print_string);

    return 0;
}