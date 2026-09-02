#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool matches_ab(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    if (str[0] != 'a') {
        return false;
    }
    
    if (str[1] == 'b' && str[2] == '\0') {
        return true;
    }
    
    if (str[1] == '\0') {
        return true;
    }
    
    return false;
}

int main() {
    const char *test_strings[] = {"a", "ab", "abc", "b", "", "ba"};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        printf("%s: %s\n", test_strings[i], matches_ab(test_strings[i]) ? "Match" : "No Match");
    }
    return 0;
}