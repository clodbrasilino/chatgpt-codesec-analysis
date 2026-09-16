#include <stdio.h>
#include <stdlib.h>

void print_string(const char *str) {
    if (str != NULL) {
        printf("%s\n", str);
    }
}

void map_strings(const char **strings, size_t count, void (*func)(const char *)) {
    if (strings == NULL || func == NULL) {
        return;
    }
    for (size_t i = 0; i < count; ++i) {
        func(strings[i]);
    }
}

int main(void) {
    const char *my_strings[] = {
        "Hello",
        "World",
        "C",
        "Programming",
        "Mapping"
    };

    size_t count = sizeof(my_strings) / sizeof(my_strings[0]);

    map_strings(my_strings, count, print_string);

    return EXIT_SUCCESS;
}