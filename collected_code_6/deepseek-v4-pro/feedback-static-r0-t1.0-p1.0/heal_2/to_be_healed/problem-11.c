#include <stdio.h>
#include <string.h>

void remove_first_last(char *str, char ch) {
    if (str == NULL || *str == '\0') {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    size_t first = (size_t)-1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            first = i;
            break;
        }
    }

    if (first == (size_t)-1) {
        return;
    }

    size_t last = (size_t)-1;
    for (size_t i = len; i > 0; i--) {
        if (str[i - 1] == ch) {
            last = i - 1;
            break;
        }
    }

    size_t write = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (size_t read = 0; read < len; read++) {
        if (read == first || read == last) {
            continue;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        str[write++] = str[read];
    }
    str[write] = '\0';
}

int main(void) {
    char str1[] = "hello world";
    remove_first_last(str1, 'o');
    printf("%s\n", str1);

    char str2[] = "a";
    remove_first_last(str2, 'a');
    printf("%s\n", str2);

    char str3[] = "aaa";
    remove_first_last(str3, 'a');
    printf("%s\n", str3);

    char str4[] = "programming";
    remove_first_last(str4, 'g');
    printf("%s\n", str4);

    char str5[] = "test";
    remove_first_last(str5, 'x');
    printf("%s\n", str5);

    return 0;
}