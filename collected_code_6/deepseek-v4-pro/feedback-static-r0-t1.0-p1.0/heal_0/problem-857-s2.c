#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*map_func)(const char *str, void *arg);

void map_strings(char **strings, size_t count, map_func func, void *arg) {
    size_t i;
    if (strings == NULL || func == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            func(strings[i], arg);
        }
    }
}

void print_string(const char *str, void *arg) {
    (void)arg;
    printf("%s\n", str);
}

int main(void) {
    char *strings[] = {
        "first string",
        "second string",
        "third string",
        "fourth string"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);

    map_strings(strings, count, print_string, NULL);

    return 0;
}