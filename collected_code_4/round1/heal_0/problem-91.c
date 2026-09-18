#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 5

int check_substring(char *strings[], char *substring, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (strstr(strings[i], substring) != NULL) {
            return 1;
        }
    }

    return 0;
}

int main() {
    char *strings[ARRAY_SIZE] = {
        "Hello",
        "World",
        "This",
        "is",
        "Example"
    };
    char substring[] = "Example";

    if (check_substring(strings, substring, ARRAY_SIZE)) {
        printf("Substring is present\n");
    } else {
        printf("Substring is not present\n");
    }

    return 0;
}