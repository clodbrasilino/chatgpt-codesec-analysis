#include <stdio.h>
#include <stddef.h>

size_t count_char_occurrences(const char *str, char c);

size_t count_char_occurrences(const char *str, char c) {
    if (str == NULL) {
        return 0;
    }

    size_t count = 0;
    while (*str != '\0') {
        if (*str == c) {
            count++;
        }
        str++;
    }

    return count;
}

int main(void) {
    const char *text = "hello world, welcome to c programming";
    char target = 'o';
    
    size_t occurrences = count_char_occurrences(text, target);
    
    printf("%zu\n", occurrences);
    
    return 0;
}