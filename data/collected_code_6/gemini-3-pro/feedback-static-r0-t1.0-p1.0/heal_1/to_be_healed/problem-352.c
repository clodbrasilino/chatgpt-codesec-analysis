#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areAllCharactersUnique(const char *str) {
    if (str == NULL) {
        return true;
    }

    bool char_set[256] = {false};

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char val = (unsigned char)str[i];
        if (char_set[val]) {
            return false;
        }
        char_set[val] = true;
    }

    return true;
}

int main(void) {
    const char *test1 = "abcdefg";
    const char *test2 = "hello";
    const char *test3 = "";
    
    if (areAllCharactersUnique(test1)) {
        printf("Test 1 passed\n");
    } else {
        printf("Test 1 failed\n");
    }

    if (!areAllCharactersUnique(test2)) {
        printf("Test 2 passed\n");
    } else {
        printf("Test 2 failed\n");
    }

    if (areAllCharactersUnique(test3)) {
        printf("Test 3 passed\n");
    } else {
        printf("Test 3 failed\n");
    }

    /* Possible weaknesses found:
     *  Condition 'areAllCharactersUnique(NULL)' is always true
     *  Calling function 'areAllCharactersUnique' returns 1
     *  Condition 'areAllCharactersUnique(NULL)' is always true [knownConditionTrueFalse]
     */
    if (areAllCharactersUnique(NULL)) {
        printf("Test 4 passed\n");
    } else {
        printf("Test 4 failed\n");
    }

    return 0;
}