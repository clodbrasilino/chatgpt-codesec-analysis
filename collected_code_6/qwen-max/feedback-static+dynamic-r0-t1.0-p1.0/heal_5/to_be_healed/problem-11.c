#include <stdio.h>
#include <string.h>

void remove_first_last_occurrence(char *str, char ch) {
    size_t len = 0;
    while (str[len] != '\0' && str[len] != ch) {
        ++len;
    }
    if (str[len] == ch) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str, str + 1, strlen(str + 1) + 1);
        --len;
    }

    int last = -1;
    for (size_t i = 0; i <= len; ++i) {
        if (str[i] == ch) {
            last = i;
        }
    }

    if (last != -1) {
        memmove(&str[last], &str[last + 1], (len - last) * sizeof(char));
        str[len - 1] = '\0';
    }
}

int main() {
    char str[] = "hello world";
    char ch = 'o';

    printf("Original string: %s\n", str);
    remove_first_last_occurrence(str, ch);
    printf("Modified string: %s\n", str);

    return 0;
}