#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 256

int contains_all_vowels(const char *str, size_t max_len)
{
    int found[5] = {0, 0, 0, 0, 0};
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        switch (tolower((unsigned char)str[i])) {
        case 'a':
            found[0] = 1;
            break;
        case 'e':
            found[1] = 1;
            break;
        case 'i':
            found[2] = 1;
            break;
        case 'o':
            found[3] = 1;
            break;
        case 'u':
            found[4] = 1;
            break;
        default:
            break;
        }
    }

    return found[0] && found[1] && found[2] && found[3] && found[4];
}

int main(void)
{
    char *input;
    size_t len;

    input = calloc(MAX_LEN, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter a string: ");

    if (fgets(input, MAX_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }

    input[MAX_LEN - 1] = '\0';

    len = strnlen(input, MAX_LEN);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (contains_all_vowels(input, MAX_LEN)) {
        printf("Accepted: the string contains all vowels\n");
    } else {
        printf("Rejected: the string does not contain all vowels\n");
    }

    free(input);
    return 0;
}