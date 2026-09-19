#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char first_repeated_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    bool seen[256] = {false};
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return str[i];
        }
        seen[c] = true;
    }

    return '\0';
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "abcdef";
    const char *test3 = "aabbcc";
    const char *test4 = "";
    const char *test5 = NULL;

    char result = first_repeated_char(test1);
    printf("First repeated in \"%s\": %c\n", test1, result != '\0' ? result : '-');

    result = first_repeated_char(test2);
    printf("First repeated in \"%s\": %c\n", test2, result != '\0' ? result : '-');

    result = first_repeated_char(test3);
    printf("First repeated in \"%s\": %c\n", test3, result != '\0' ? result : '-');

    result = first_repeated_char(test4);
    printf("First repeated in \"%s\": %c\n", test4, result != '\0' ? result : '-');

    if (test5 != NULL) {
        result = first_repeated_char(test5);
        printf("First repeated in NULL: %c\n", result != '\0' ? result : '-');
    } else {
        printf("First repeated in NULL: -\n");
    }

    return 0;
}