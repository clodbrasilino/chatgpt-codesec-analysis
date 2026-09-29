#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void count_characters(const char *str, int *alphabets, int *digits, int *specials) {
    if (str == NULL || alphabets == NULL || digits == NULL || specials == NULL) {
        return;
    }

    *alphabets = 0;
    *digits = 0;
    *specials = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            (*alphabets)++;
        } else if (isdigit((unsigned char)str[i])) {
            (*digits)++;
        } else if (!isspace((unsigned char)str[i])) {
            (*specials)++;
        }
    }
}

int main(void) {
    size_t buf_size = 256;
    char *input_string = (char *)malloc(buf_size * sizeof(char));
    int alphabets = 0;
    int digits = 0;
    int specials = 0;

    if (input_string != NULL) {
        if (fgets(input_string, (int)buf_size, stdin) != NULL) {
            count_characters(input_string, &alphabets, &digits, &specials);
            
            printf("Alphabets: %d\n", alphabets);
            printf("Digits: %d\n", digits);
            printf("Special Characters: %d\n", specials);
        }
        free(input_string);
    }

    return 0;
}