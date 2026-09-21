#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

void count_digits_letters(const char *str, int *digits, int *letters) {
    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }

    *digits = 0;
    *letters = 0;

    while (*str != '\0') {
        if (isdigit((unsigned char)*str)) {
            (*digits)++;
        } else if (isalpha((unsigned char)*str)) {
            (*letters)++;
        }
        str++;
    }
}

int main(void) {
    char str[BUFFER_SIZE];
    int digits = 0;
    int letters = 0;
    size_t len;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else if (len == sizeof(str) - 1 && str[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    count_digits_letters(str, &digits, &letters);

    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);

    return 0;
}