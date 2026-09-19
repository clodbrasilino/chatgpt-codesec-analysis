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

    for (const char *p = str; *p; p++) {
        if (isupper(*p)) {
            counts.uppercase++;
        } else if (islower(*p)) {
            counts.lowercase++;
        } else if (isdigit(*p)) {
            counts.numeric++;
        } else {
            counts.special++;
        }
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