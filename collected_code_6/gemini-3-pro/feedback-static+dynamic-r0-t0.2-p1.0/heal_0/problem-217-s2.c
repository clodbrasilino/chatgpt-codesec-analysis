#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int seen[256] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return str[i];
        }
        seen[c] = 1;
    }

    return '\0';
}

int main(void) {
    const char *test_str1 = "programming";
    const char *test_str2 = "abcdefg";
    const char *test_str3 = NULL;

    char res1 = find_first_repeated_char(test_str1);
    char res2 = find_first_repeated_char(test_str2);
    char res3 = find_first_repeated_char(test_str3);

    if (res1 != '\0') {
        printf("First repeated char in '%s': %c\n", test_str1, res1);
    } else {
        printf("No repeated char in '%s'\n", test_str1);
    }

    if (res2 != '\0') {
        printf("First repeated char in '%s': %c\n", test_str2, res2);
    } else {
        printf("No repeated char in '%s'\n", test_str2);
    }

    if (res3 != '\0') {
        printf("First repeated char in NULL string: %c\n", res3);
    } else {
        printf("No repeated char in NULL string\n");
    }

    return 0;
}