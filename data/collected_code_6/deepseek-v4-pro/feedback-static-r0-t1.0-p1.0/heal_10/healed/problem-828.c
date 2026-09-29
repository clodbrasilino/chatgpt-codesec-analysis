#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count_chars(const char *str, int *alphabets, int *digits, int *specials) {
    *alphabets = 0;
    *digits = 0;
    *specials = 0;

    if (str == NULL) {
        return;
    }

    for (const char *p = str; *p != '\0'; p++) {
        if (isalpha((unsigned char)*p)) {
            (*alphabets)++;
        }
        else if (isdigit((unsigned char)*p)) {
            (*digits)++;
        }
        else {
            (*specials)++;
        }
    }
}

#include <stdlib.h>

int main(void) {
    char *str = NULL;
    size_t buffer_size = 0;
    int alphabets, digits, specials;

    printf("Enter a string: ");

    ssize_t len = getline(&str, &buffer_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(str);
        return 1;
    }

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        count_chars(str, &alphabets, &digits, &specials);
    } else {
        count_chars(str, &alphabets, &digits, &specials);
    }

    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", specials);

    free(str);
    return 0;
}