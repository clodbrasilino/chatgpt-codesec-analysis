#include <stdio.h>
#include <string.h>

int contains_z(const char *str) {
    if (str == NULL) return 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == 'z') return 1;
    }
    return 0;
}

int main() {
    const char *test_strings[] = {"hello", "world", "zebra", "lazy", "dizzy"};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        if (contains_z(test_strings[i])) {
            printf("%s contains 'z'\n", test_strings[i]);
        } else {
            printf("%s does not contain 'z'\n", test_strings[i]);
        }
    }
    return 0;
}