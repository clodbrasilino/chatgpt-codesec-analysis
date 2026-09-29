#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int uppercase_count;
    int lowercase_count;
    int special_count;
    int numeric_count;
} CharCounts;

void count_characters(const char *str, CharCounts *counts) {
    if (str == NULL || counts == NULL) {
        return;
    }

    counts->uppercase_count = 0;
    counts->lowercase_count = 0;
    counts->special_count = 0;
    counts->numeric_count = 0;

    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            counts->uppercase_count++;
        } else if (islower((unsigned char)*str)) {
            counts->lowercase_count++;
        } else if (isdigit((unsigned char)*str)) {
            counts->numeric_count++;
        } else {
            counts->special_count++;
        }
        str++;
    }
}

int main(void) {
    const char *test_string = "Hello World! 123";
    CharCounts counts;

    count_characters(test_string, &counts);

    printf("Input string: %s\n", test_string);
    printf("Uppercase characters: %d\n", counts.uppercase_count);
    printf("Lowercase characters: %d\n", counts.lowercase_count);
    printf("Special characters: %d\n", counts.special_count);
    printf("Numeric characters: %d\n", counts.numeric_count);

    return 0;
}