#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *capitalize_first_last(char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return str;
    }

    size_t i = 0;
    while (i < len) {
        if (isalpha((unsigned char)str[i])) {
            size_t start = i;
            while (i < len && isalpha((unsigned char)str[i])) {
                i++;
            }
            size_t end = i - 1;

            if (islower((unsigned char)str[start])) {
                str[start] = (char)toupper((unsigned char)str[start]);
            }

            if (start != end) {
                if (islower((unsigned char)str[end])) {
                    str[end] = (char)toupper((unsigned char)str[end]);
                }
            }
        } else {
            i++;
        }
    }

    return str;
}

int main(void) {
    char str1[] = "hello world";
    char str2[] = "c programming is fun";
    char str3[] = "a";
    char str4[] = "  multiple   spaces  ";

    printf("%s\n", capitalize_first_last(str1));
    printf("%s\n", capitalize_first_last(str2));
    printf("%s\n", capitalize_first_last(str3));
    printf("%s\n", capitalize_first_last(str4));

    return 0;
}