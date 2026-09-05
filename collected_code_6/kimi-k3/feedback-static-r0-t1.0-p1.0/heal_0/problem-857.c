#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_string(const char *str)
{
    if (str != NULL) {
        printf("%s\n", str);
    }
}

void map_strings(char **strings, size_t count, void (*func)(const char *))
{
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

int main(void)
{
    char *strings[] = {
        "Hello",
        "World",
        "C",
        "Programming",
        "Language"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    
    map_strings(strings, count, print_string);
    
    return 0;
}