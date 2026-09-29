#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_ab(const char *str) {
    if (str == NULL) return false;
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
        if (str[i] != 'a' && (i == 0 || str[i-1] != 'a')) return false;
        if (str[i] != 'b' && (i == 0 || str[i-1] != 'a')) return false;
    }
    return true;
}

int main() {
    const char *test_strings[] = {
        "a", "ab", "aab", "abb", "b", "ac", "abc"
    };
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        printf("'%s': %s\n", test_strings[i], match_ab(test_strings[i]) ? "Match" : "No Match");
    }
    return 0;
}