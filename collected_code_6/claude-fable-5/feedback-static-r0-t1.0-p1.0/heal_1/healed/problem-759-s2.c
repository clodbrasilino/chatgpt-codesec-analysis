#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_SIZE 128

bool is_decimal_with_precision_two(const char *str);

bool is_decimal_with_precision_two(const char *str)
{
    size_t i = 0;
    size_t digits_before = 0;
    size_t digits_after = 0;

    if (str == NULL || str[0] == '\0') {
        return false;
    }

    if (str[i] == '+' || str[i] == '-') {
        i++;
    }

    while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
        digits_before++;
        i++;
    }

    if (digits_before == 0) {
        return false;
    }

    if (str[i] != '.') {
        return false;
    }
    i++;

    while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
        digits_after++;
        i++;
    }

    if (str[i] != '\0') {
        return false;
    }

    return digits_after == 2;
}

int main(void)
{
    char buffer[BUFFER_SIZE];

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\r\n")] = '\0';

    if (is_decimal_with_precision_two(buffer)) {
        printf("Valid decimal with precision 2\n");
    } else {
        printf("Invalid decimal with precision 2\n");
    }

    return EXIT_SUCCESS;
}