#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool has_letter_and_number(const char *str, size_t max_len)
{
    bool has_letter = false;
    bool has_digit = false;
    size_t i;

    if (str == NULL) {
        return false;
    }

    for (i = 0U; i < max_len && str[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)str[i];
        if (isalpha(ch)) {
            has_letter = true;
        } else if (isdigit(ch)) {
            has_digit = true;
        }
        if (has_letter && has_digit) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0U;
    ssize_t read_len;
    size_t len;

    read_len = getline(&buffer, &buffer_size, stdin);
    if (read_len < 0) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    len = (size_t)read_len;
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    }

    if (has_letter_and_number(buffer, len + 1U)) {
        printf("The string contains at least one letter and one number.\n");
    } else {
        printf("The string does not contain both a letter and a number.\n");
    }

    free(buffer);
    return EXIT_SUCCESS;
}