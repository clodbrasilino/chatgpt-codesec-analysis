#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_matching_chars(const char *str) {
    if (str == NULL) {
        return 0;
    }
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (islower((unsigned char)str[i])) {
            if (str[i] - 'a' == (int)i) {
                count++;
            }
        } else if (isupper((unsigned char)str[i])) {
            if (str[i] - 'A' == (int)i) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    const char *test_str = "AbCdEfGhIjKlMnOpQrStUvWxYz";
    int result = count_matching_chars(test_str);
    printf("%d\n", result);
    return 0;
}