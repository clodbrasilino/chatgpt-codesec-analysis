#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_lowercase_with_underscore(const char *str) {
    int found = 0;
    while (*str) {
        if (islower((unsigned char)*str)) {
            str++;
            continue;
        }
        if (*str == '_') {
            if (found && *(str + 1) == '\0') return 0; // Ensure there are no trailing underscores
            found = 1;
            str++;
            continue;
        }
        return 0;
    }
    return found;
}

int main() {
    const char *test_strings[] = {"a_b", "ab", "A_b", "a_B", "a_b_c", "_a_b", "a_b_", "abc_def", "123"};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        printf("'%s': %s\n", test_strings[i], is_lowercase_with_underscore(test_strings[i]) ? "Valid" : "Invalid");
    }
    return 0;
}