#include <stdio.h>
#include <string.h>

size_t count_char(const char *str, char ch) {
    size_t count = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str != '\0') {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    return count;
}

int main(void) {
    char buffer[256];
    char ch;
    size_t result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    printf("Enter a character to count: ");
    if (scanf(" %c", &ch) != 1) {
        fprintf(stderr, "Error reading character.\n");
        return 1;
    }

    result = count_char(buffer, ch);
    printf("The character '%c' appears %zu time(s) in the string.\n", ch, result);

    return 0;
}