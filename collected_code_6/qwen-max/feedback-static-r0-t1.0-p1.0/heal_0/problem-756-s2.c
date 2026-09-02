#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_ab(const char *str) {
    if (strlen(str) > 0 && str[0] == 'a') {
        if (strlen(str) == 1 || (strlen(str) == 2 && str[1] == 'b')) {
            return true;
        }
    }
    return false;
}

int main() {
    const char* test_strings[] = {"a", "ab", "ac", "abc", "b", ""};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        printf("Testing '%s': %s\n", test_strings[i], match_ab(test_strings[i]) ? "Match" : "No Match");
    }
    return 0;
}