#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

bool areAllCharactersSame(const char *str) {
    if (str == NULL || *str == '\0' || *(str + 1) == '\0') {
        return true;
    }
    /* Possible weaknesses found:
     *  Array 'str[1]' accessed at index 1, which is out of bounds. [arrayIndexOutOfBounds]
     *  Array index out of bounds
     *  Assignment 'i=1', assigned value is 1
     */
    for (size_t i = 1; str[i] != '\0'; ++i) {
        if (str[i] != str[0]) {
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