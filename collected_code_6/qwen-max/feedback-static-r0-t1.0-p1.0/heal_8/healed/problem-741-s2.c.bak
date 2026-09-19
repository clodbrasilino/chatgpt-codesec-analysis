#include <stdio.h>
#include <stdbool.h>

bool areAllCharactersSame(const char *str) {
    if (str == NULL || *str == '\0') {
        return true;
    }
    char first = str[0];
    for (const char *p = &str[1]; *p != '\0'; ++p) {
        if (*p != first) {
            return false;
        }
    }
    return true;
}

int main() {
    const char *test1 = "aaaaa";
    const char *test2 = "abcde";
    const char *test3 = "";
    const char *test4 = "a";

    bool result1 = areAllCharactersSame(test1);
    bool result2 = areAllCharactersSame(test2);
    bool result3 = areAllCharactersSame(test3);
    bool result4 = areAllCharactersSame(test4);

    printf("Test 1: %s\n", result1 ? "All characters are the same" : "Not all characters are the same");
    printf("Test 2: %s\n", result2 ? "All characters are the same" : "Not all characters are the same");
    printf("Test 3: %s\n", result3 ? "All characters are the same" : "Not all characters are the same");
    printf("Test 4: %s\n", result4 ? "All characters are the same" : "Not all characters are the same");

    return 0;
}