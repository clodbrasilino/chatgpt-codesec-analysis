#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str, size_t len) {
    if (len < 2) {
        return false;
    }
    if (str[0] == 'a' && str[len - 1] == 'b') {
        return true;
    }
    return false;
}

int main() {
    const char *test_strings[] = {"ab", "a123b", "acb", "a b", "aab", "b", "a"};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; ++i) {
        const char *str = test_strings[i];
        size_t len = strnlen(str, 100);
        bool result = match_pattern(str, len);
        printf("Testing: %s, Result: %s\n", str, result ? "Match" : "No Match");
    }

    return 0;
}