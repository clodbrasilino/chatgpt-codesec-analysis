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

#define BUFFER_SIZE 512

int main(void) {
    char str[BUFFER_SIZE] = {0};
    int alphabets, digits, specials;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    if (len == 0 && str[0] == '\0') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    count_chars(str, &alphabets, &digits, &specials);

    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", specials);

    return 0;
}