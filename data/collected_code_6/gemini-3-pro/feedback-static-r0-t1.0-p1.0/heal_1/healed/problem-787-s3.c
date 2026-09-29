#include <stdio.h>
#include <stdlib.h>

int match_a_three_b(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int state = 0;
    for (const char *p = str; *p != '\0'; p++) {
        if (state == 0) {
            if (*p == 'a') state = 1;
        } else if (state == 1) {
            if (*p == 'b') state = 2;
            else if (*p == 'a') state = 1;
            else state = 0;
        } else if (state == 2) {
            if (*p == 'b') state = 3;
            else if (*p == 'a') state = 1;
            else state = 0;
        } else if (state == 3) {
            if (*p == 'b') return 1;
            else if (*p == 'a') state = 1;
            else state = 0;
        }
    }

    return 0;
}

int main(void) {
    const char *test_cases[] = {
        "abbb",
        "xabbbx",
        "ab",
        "abb",
        "abbbb",
        "bbaaaabbb",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; i++) {
        int result = match_a_three_b(test_cases[i]);
        if (result) {
            printf("Match found in: %s\n", test_cases[i]);
        } else {
            printf("No match in: %s\n", test_cases[i]);
        }
    }

    return 0;
}