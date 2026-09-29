#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*map_func)(const char *str);

void print_string(const char *str) {
    if (str != NULL) {
        printf("%s\n", str);
    }
}

void map_strings(const char **strings, size_t count, map_func func) {
    size_t i;
    
    if (strings == NULL || func == NULL) {
        return;
    }
    
    for (i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            func(strings[i]);
        }
    }
}

int main(void) {
    const char *strings[] = {
        "First string",
        "Second string",
        "Third string",
        "Fourth string",
        "Fifth string"
    };
    
    size_t count = sizeof(strings) / sizeof(strings[0]);
    
    map_strings(strings, count, print_string);
    
    return 0;
}