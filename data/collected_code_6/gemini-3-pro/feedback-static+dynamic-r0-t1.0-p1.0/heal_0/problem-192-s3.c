#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool hasLetterAndNumber(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool hasLetter = false;
    bool hasNumber = false;

    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            hasLetter = true;
        } else if (isdigit((unsigned char)*str)) {
            hasNumber = true;
        }

        if (hasLetter && hasNumber) {
            return true;
        }

        str++;
    }

    return false;
}

int main(void) {
    const char *testCases[] = {
        "password123",
        "onlyletters",
        "123456789",
        "nolettersornumbers!",
        "a1",
        "",
        NULL
    };

    size_t numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (size_t i = 0; i < numTestCases; i++) {
        if (hasLetterAndNumber(testCases[i])) {
            printf("Test case %zu: Valid\n", i);
        } else {
            printf("Test case %zu: Invalid\n", i);
        }
    }

    return 0;
}