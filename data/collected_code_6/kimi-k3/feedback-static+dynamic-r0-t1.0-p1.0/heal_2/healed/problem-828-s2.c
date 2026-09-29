#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void count_characters(const char *str, int *alphabets, int *digits, int *special_chars) {
    if (str == NULL || alphabets == NULL || digits == NULL || special_chars == NULL) {
        return;
    }

    *alphabets = 0;
    *digits = 0;
    *special_chars = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isalpha(c)) {
            (*alphabets)++;
        } else if (isdigit(c)) {
            (*digits)++;
        } else {
            (*special_chars)++;
        }
    }
}

int main(void) {
    char *str = NULL;
    size_t size = 0;
    ssize_t len;
    int alphabets = 0, digits = 0, special_chars = 0;

    printf("Enter a string: ");
    
    len = getline(&str, &size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str);
        return 1;
    }

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    count_characters(str, &alphabets, &digits, &special_chars);

    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special Characters: %d\n", special_chars);

    free(str);
    return 0;
}