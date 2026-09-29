#include <stdio.h>
#include <string.h>
#include <ctype.h>

size_t count_vowels(const char *str) {
    size_t count = 0;
    if (str == NULL) {
        return 0;
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = tolower((unsigned char)str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    const char *text = "Hello World";
    size_t num_vowels = count_vowels(text);
    printf("%zu\n", num_vowels);
    return 0;
}