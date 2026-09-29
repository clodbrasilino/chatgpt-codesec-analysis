#include <stdio.h>
#include <string.h>

void remove_first_last_occurrence(char *str, char ch) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int first = -1;
    int last = -1;

    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            if (first == -1) {
                first = i;
            }
            last = i;
        }
    }

    if (first != -1) {
        if (first == last) {
            for (int i = first; i < len; i++) {
                str[i] = str[i + 1];
            }
        } else {
            for (int i = last; i < len; i++) {
                str[i] = str[i + 1];
            }
            len--; 
            for (int i = first; i < len; i++) {
                str[i] = str[i + 1];
            }
        }
    }
}

int main(void) {
    char str1[] = "hello world";
    remove_first_last_occurrence(str1, 'l');
    printf("%s\n", str1);

    char str2[] = "programming";
    remove_first_last_occurrence(str2, 'r');
    printf("%s\n", str2);

    char str3[] = "abcd";
    remove_first_last_occurrence(str3, 'z');
    printf("%s\n", str3);

    char str4[] = "test";
    remove_first_last_occurrence(str4, 't');
    printf("%s\n", str4);

    return 0;
}