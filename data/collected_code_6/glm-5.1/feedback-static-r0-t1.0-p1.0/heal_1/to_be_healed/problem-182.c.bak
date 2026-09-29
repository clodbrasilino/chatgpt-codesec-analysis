#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

typedef struct {
    int uppercase;
    int lowercase;
    int numeric;
    int special;
} CharCounts;

CharCounts count_char_types(const char *str) {
    CharCounts counts = {0, 0, 0, 0};
    regex_t regex;
    /* Possible weaknesses found:
     *  The scope of the variable 'ret' can be reduced. [variableScope]
     */
    int ret;

    if (str == NULL) {
        return counts;
    }

    const char *patterns[4] = {
        "[A-Z]",
        "[a-z]",
        "[0-9]",
        "[^A-Za-z0-9]"
    };

    for (int i = 0; i < 4; i++) {
        ret = regcomp(&regex, patterns[i], REG_EXTENDED);
        if (ret != 0) {
            continue;
        }

        const char *p = str;
        while (*p) {
            if (regexec(&regex, p, 0, NULL, 0) == 0) {
                switch (i) {
                    case 0: counts.uppercase++; break;
                    case 1: counts.lowercase++; break;
                    case 2: counts.numeric++; break;
                    case 3: counts.special++; break;
                }
            }
            p++;
        }

        regfree(&regex);
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