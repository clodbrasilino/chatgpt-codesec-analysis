#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    if (str == NULL || str[0] != 'a') return false;

    size_t len = strlen(str);
    for (size_t i = 1; i < len; ++i) {
        if (str[i] != 'b') return false;
    }

    return true;
}

int main() {
    const char *test1 = "ab";
    const char *test2 = "abb";
    const char *test3 = "a";
    const char *test4 = "ac";
    const char *test5 = "abc";

    printf("%s: %s\n", test1, match_pattern(test1) ? "Match" : "No Match");
    printf("%s: %s\n", test2, match_pattern(test2) ? "Match" : "No Match");
    printf("%s: %s\n", test3, match_pattern(test3) ? "Match" : "No Match");
    printf("%s: %s\n", test4, match_pattern(test4) ? "Match" : "No Match");
    printf("%s: %s\n", test5, match_pattern(test5) ? "Match" : "No Match");

    return 0;
}