#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>

typedef struct {
    int uppercase;
    int lowercase;
    int numeric;
    int special;
} CharCounts;

CharCounts count_char_types(const char *str) {
    CharCounts counts = {0, 0, 0, 0};

    if (str == NULL) {
        return counts;
    }

    while (*str) {
        if (isupper((unsigned char)*str)) {
            counts.uppercase++;
        } else if (islower((unsigned char)*str)) {
            counts.lowercase++;
        } else if (isdigit((unsigned char)*str)) {
            counts.numeric++;
        } else {
            counts.special++;
        }
        str++;
    }

    return counts;
}

int main(void) {
    const char *test_str = "Hello World! 123 @#$";
    CharCounts result = count_char_types(test_str);

    printf("Uppercase: %d\n", result.uppercase);
    printf("Lowercase: %d\n", result.lowercase);
    printf("Numeric: %d\n", result.numeric);
    printf("Special: %d\n", result.special);

    return 0;
}