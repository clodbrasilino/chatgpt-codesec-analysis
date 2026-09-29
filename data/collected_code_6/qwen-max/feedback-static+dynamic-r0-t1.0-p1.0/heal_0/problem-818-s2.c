#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_lowercase(const char *str) {
    int count = 0;
    while (*str) {
        if (islower((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int main() {
    const char *test_string = "Hello, World!";
    int lowercase_count = count_lowercase(test_string);
    printf("Lowercase letters: %d\n", lowercase_count);
    return 0;
}