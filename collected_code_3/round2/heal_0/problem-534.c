#include <stdio.h>
#include <string.h>

int find_pattern(char *str, char *pattern) {
    char *result = strstr(str, pattern);
    if (result) {
        return result - str;
    } else {
        return -1;
    }
}

int main() {
    char str[] = "Hello, World!";
    char pattern[] = "World";
    int location = find_pattern(str, pattern);
    if (location != -1) {
        printf("Pattern found at location %d\n", location);
    } else {
        printf("Pattern not found\n");
    }
    return 0;
}