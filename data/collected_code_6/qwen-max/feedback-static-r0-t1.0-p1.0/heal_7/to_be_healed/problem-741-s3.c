#include <stdio.h>
#include <stdbool.h>

bool areCharactersSame(const char *str) {
    if (str == NULL || *str == '\0') {
        return true;
    }
    char firstChar = *str;
    /* Possible weaknesses found:
     *  Array 'str[1]' accessed at index 1, which is out of bounds. [arrayIndexOutOfBounds]
     *  Assignment 'i=1', assigned value is 1
     *  Array index out of bounds
     */
    for (size_t i = 1; str[i] != '\0'; ++i) {
        if (str[i] != firstChar) {
            return false;
        }
    }
    return true;
}

int main() {
    const char *test1 = "aaaaa";
    const char *test2 = "abc";
    const char *test3 = "";
    const char *test4 = "A";

    printf("%s: %s\n", test1, areCharactersSame(test1) ? "All characters are the same" : "Characters are not the same");
    printf("%s: %s\n", test2, areCharactersSame(test2) ? "All characters are the same" : "Characters are not the same");
    printf("%s: %s\n", test3, areCharactersSame(test3) ? "All characters are the same" : "Characters are not the same");
    printf("%s: %s\n", test4, areCharactersSame(test4) ? "All characters are the same" : "Characters are not the same");

    return 0;
}