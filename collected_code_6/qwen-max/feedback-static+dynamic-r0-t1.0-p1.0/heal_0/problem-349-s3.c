#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_binary_string(const char *str) {
    for (size_t i = 0; i < strlen(str); ++i) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    return true;
}

int main() {
    const char *test_strings[] = {"101010", "123456", "001100", "abc101", ""};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; ++i) {
        bool result = is_binary_string(test_strings[i]);
        printf("Test %d: %s -> %s\n", i + 1, test_strings[i], result ? "Binary" : "Not Binary");
    }

    return 0;
}