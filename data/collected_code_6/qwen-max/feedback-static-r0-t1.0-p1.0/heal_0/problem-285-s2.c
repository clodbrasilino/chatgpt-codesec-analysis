#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_ab(const char *str) {
    if (str == NULL) return false;

    size_t len = strlen(str);
    if (len < 3 || len > 4) return false;

    if (str[0] != 'a') return false;

    for (size_t i = 1; i < len; ++i) {
        if (str[i] != 'b') return false;
    }

    return true;
}

int main() {
    const char *test1 = "abb";
    const char *test2 = "abbb";
    const char *test3 = "a";

    printf("%s: %s\n", test1, match_ab(test1) ? "Match" : "No Match");
    printf("%s: %s\n", test2, match_ab(test2) ? "Match" : "No Match");
    printf("%s: %s\n", test3, match_ab(test3) ? "Match" : "No Match");

    return 0;
}