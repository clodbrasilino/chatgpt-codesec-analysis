#include <stdio.h>
#include <stdbool.h>

bool match_pattern(const char *str, size_t len) {
    if (len < 2 || str[len - 2] != 'b' || str[0] != 'a') {
        return false;
    }
    return true;
}

int main(void) {
    const char *test_strings[] = {"ab", "a123b", "a_b", "abc", "acb", "b"};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        size_t len = 0;
        /* Possible weaknesses found:
         *  Condition 'test_strings[i][len]!='\0'' is always true [knownConditionTrueFalse]
         */
        while (test_strings[i][len] != '\0' && test_strings[i][len] != '\0') {
            len++;
        }
        if (match_pattern(test_strings[i], len)) {
            printf("Match: %s\n", test_strings[i]);
        } else {
            printf("No match: %s\n", test_strings[i]);
        }
    }
    return 0;
}