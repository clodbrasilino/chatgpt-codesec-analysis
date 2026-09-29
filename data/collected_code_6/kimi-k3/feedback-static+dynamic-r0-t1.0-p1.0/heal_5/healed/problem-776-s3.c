#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_vowel(char c) {
    c = (char)tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

size_t count_chars_with_vowel_neighbors(const char *str, size_t maxlen) {
    size_t count = 0;
    size_t len;
    size_t i;

    if (str == NULL || maxlen == 0) {
        return 0;
    }

    len = strnlen(str, maxlen);
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
    ssize_t line_length;
    size_t result;

    printf("Enter a string: ");
    
    line_length = getline(&buffer, &buffer_size, stdin);
    if (line_length == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    if (line_length > 0 && buffer[line_length - 1] == '\n') {
        buffer[line_length - 1] = '\0';
        line_length--;
    }

    result = count_chars_with_vowel_neighbors(buffer, (size_t)line_length + 1);
    printf("Count: %zu\n", result);

    free(buffer);
    return 0;
}