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
        size_t len = strlen(test_strings[i]);
        bool result = match_pattern(test_strings[i], len);
        printf("Testing: %s, Result: %s\n", test_strings[i], result ? "Match" : "No Match");
    }

    return 0;
}