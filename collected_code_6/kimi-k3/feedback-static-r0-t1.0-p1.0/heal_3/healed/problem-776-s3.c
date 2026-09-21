#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_vowel(char c) {
    c = (char)tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

size_t count_chars_with_vowel_neighbors(const char *str, size_t max_len) {
    size_t count = 0;
    size_t len = 0;
    size_t i;

    if (str == NULL || max_len == 0) {
        return 0;
    }

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    if (len < 3) {
        return 0;
    }

    for (i = 1; i < len - 1; i++) {
        if (is_vowel(str[i - 1]) && is_vowel(str[i + 1])) {
            count++;
        }
    }

    return count;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;
    size_t result;

    printf("Enter a string: ");
    
    read_len = getline(&buffer, &buffer_size, stdin);
    
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    if (read_len > 0 && buffer[read_len - 1] == '\n') {
        buffer[read_len - 1] = '\0';
        read_len--;
    }

    result = count_chars_with_vowel_neighbors(buffer, (size_t)read_len);
    printf("Count: %zu\n", result);

    free(buffer);
    return 0;
}