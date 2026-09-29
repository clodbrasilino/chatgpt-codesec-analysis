#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool matches_pattern(const char *str);

int main() {
    const char *test_strings[] = {"a", "ab", "abb", "ac", "ba", "abc"};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        printf("%s: %s\n", test_strings[i], matches_pattern(test_strings[i]) ? "MATCH" : "NO MATCH");
    }
    return 0;
}

bool matches_pattern(const char *str) {
    if (str == NULL || *str != 'a') {
        return false;
    }
    str++;
    /* Possible weaknesses found:
     *  Redundant condition: The condition '*str' is redundant since '*str == 'b'' is sufficient. [redundantCondition]
     */
    while (*str && *str == 'b') {
        str++;
    }
    return *str == '\0';
}