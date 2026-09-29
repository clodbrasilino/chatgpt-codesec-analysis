#include <stdio.h>
#include <stdlib.h>

void print_string(char *str) {
    printf("%s\n", str);
}

void map_strings(char **array, size_t len, void (*func)(char *)) {
    for (size_t i = 0; i < len; i++) {
        if (array[i] != NULL) {
            func(array[i]);
        }
    }
}

int main() {
    char *strings[] = {"Hello", "World", "C", "Programming"};
    size_t length = sizeof(strings) / sizeof(strings[0]);

    map_strings(strings, length, print_string);

    return 0;
}