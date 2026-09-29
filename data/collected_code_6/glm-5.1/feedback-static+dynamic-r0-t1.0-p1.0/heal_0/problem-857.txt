#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef void (*MapFunction)(const char *);

void map_strings(char **strings, size_t count, MapFunction func) {
    if (strings == NULL || func == NULL) {
        return;
    }
    for (size_t i = 0; i < count; ++i) {
        if (strings[i] != NULL) {
            func(strings[i]);
        }
    }
}

void print_string(const char *str) {
    if (str != NULL) {
        printf("%s\n", str);
    }
}

int main(void) {
    char *strings[] = {
        "alpha",
        "bravo",
        "charlie",
        "delta",
        "echo",
        NULL
    };
    
    size_t count = sizeof(strings) / sizeof(strings[0]);
    
    if (strings[count - 1] == NULL) {
        count = count - 1;
    }
    
    map_strings(strings, count, print_string);
    
    return 0;
}