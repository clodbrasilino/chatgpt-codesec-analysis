#include <stdio.h>
#include <stdlib.h>

typedef void (*MapFunction)(const char *);

void map(char **strings, size_t size, MapFunction func) {
    if (strings == NULL || func == NULL) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        if (strings[i] != NULL) {
            func(strings[i]);
        }
    }
}

void print_string(const char *str) {
    printf("%s\n", str);
}

int main(void) {
    char *strings[] = {"apple", "banana", "cherry"};
    size_t size = sizeof(strings) / sizeof(strings[0]);
    map(strings, size, print_string);
    return 0;
}