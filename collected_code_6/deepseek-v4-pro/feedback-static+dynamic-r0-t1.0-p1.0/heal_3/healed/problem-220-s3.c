#include <stdio.h>
#include <string.h>
#include <limits.h>

void replace_chars(char *str, size_t n) {
    size_t count = 0;
    while (*str && count < n) {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
            count++;
        }
        str++;
    }
}

size_t safe_str_to_size_t(const char *input) {
    unsigned long long val;
    char *endptr;
    val = strtoull(input, &endptr, 10);
    if (endptr == input || *endptr != '\0' || val > SIZE_MAX) {
        return 0;
    }
    return (size_t)val;
}

int main(void) {
    char text[256];
    char max_replace_str[32];
    size_t max_replace;

    printf("Enter a string: ");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 1;
    }
    text[strcspn(text, "\n")] = '\0';

    printf("Enter maximum replacements: ");
    if (fgets(max_replace_str, sizeof(max_replace_str), stdin) == NULL) {
        return 1;
    }

    max_replace = safe_str_to_size_t(max_replace_str);

    replace_chars(text, max_replace);
    printf("Result: %s\n", text);

    return 0;
}