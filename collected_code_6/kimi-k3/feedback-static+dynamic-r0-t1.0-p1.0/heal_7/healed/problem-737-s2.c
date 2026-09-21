#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int starts_with_vowel(const char *str) {
    regex_t regex;
    int ret;
    int result = 0;

    if (str == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "^[aeiouAEIOU]", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strnlen(buffer, sizeof(buffer));

        if (len == sizeof(buffer) && buffer[len - 1] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            buffer[sizeof(buffer) - 1] = '\0';
        } else if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else if (len == 0) {
            buffer[0] = '\0';
        }

        if (starts_with_vowel(buffer)) {
            printf("The string starts with a vowel.\n");
        } else {
            printf("The string does not start with a vowel.\n");
        }
    }

    return 0;
}