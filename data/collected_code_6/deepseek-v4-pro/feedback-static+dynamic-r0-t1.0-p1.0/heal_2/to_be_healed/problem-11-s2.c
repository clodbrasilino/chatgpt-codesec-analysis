#include <stdio.h>
#include <string.h>

void remove_first_last_occurrence(char *str, char ch) {
    if (str == NULL || *str == '\0') {
        return;
    }

    int first = -1;
    int last = -1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            if (first == -1) {
                first = i;
            }
            last = i;
        }
    }

    if (first == -1) {
        return;
    }

    if (first == last) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(&str[first], &str[first + 1], strlen(str) - first);
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    memmove(&str[last], &str[last + 1], strlen(str) - last);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    memmove(&str[first], &str[first + 1], strlen(str) - first);
}

int main(void) {
    char str1[] = "hello world";
    remove_first_last_occurrence(str1, 'o');
    printf("%s\n", str1);

    char str2[] = "aaaa";
    remove_first_last_occurrence(str2, 'a');
    printf("%s\n", str2);

    char str3[] = "character";
    remove_first_last_occurrence(str3, 'a');
    printf("%s\n", str3);

    char str4[] = "test";
    remove_first_last_occurrence(str4, 'x');
    printf("%s\n", str4);

    char str5[] = "single";
    remove_first_last_occurrence(str5, 'g');
    printf("%s\n", str5);

    return 0;
}