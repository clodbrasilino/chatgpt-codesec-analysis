#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

size_t count_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t count = 0;
    while (*str != '\0') {
        char ch = tolower((unsigned char)*str);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }
        str++;
    }

    return count;
}

int main(void) {
    const char *test_str = "Hello, World!";
    size_t vowels = count_vowels(test_str);
    printf("Number of vowels: %zu\n", vowels);
    return 0;
}