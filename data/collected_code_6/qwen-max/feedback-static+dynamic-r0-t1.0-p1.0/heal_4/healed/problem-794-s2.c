#include <stdio.h>
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
    struct test_case {
        const char *str;
        size_t len;
    };

    struct test_case test_strings[] = {
        {"ab", 2},
        {"a123b", 5},
        {"acb", 3},
        {"a b", 3},
        {"aab", 3},
        {"b", 1},
        {"a", 1}
    };
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; ++i) {
        bool result = match_pattern(test_strings[i].str, test_strings[i].len);
        printf("Testing: %s, Result: %s\n", test_strings[i].str, result ? "Match" : "No Match");
    }

    return 0;
}