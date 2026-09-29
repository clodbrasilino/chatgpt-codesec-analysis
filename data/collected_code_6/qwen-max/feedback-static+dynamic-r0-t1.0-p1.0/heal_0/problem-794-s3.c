#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    if (str == NULL) return false;
    size_t len = strlen(str);
    if (len < 2) return false;
    if (str[0] != 'a' || str[len - 1] != 'b') return false;
    return true;
}

int main() {
    const char *test_strings[] = {"ab", "a123b", "acdb", "ba", "a", ""};
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        if (match_pattern(test_strings[i])) {
            printf("'%s' matches the pattern.\n", test_strings[i]);
        } else {
            printf("'%s' does not match the pattern.\n", test_strings[i]);
        }
    }

    return 0;
}