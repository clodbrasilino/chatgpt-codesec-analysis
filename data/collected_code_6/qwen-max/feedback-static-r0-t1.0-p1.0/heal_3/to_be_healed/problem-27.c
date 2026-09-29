#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Possible weaknesses found:
 *  expected 'char *' but argument is of type 'char'
 *  passing argument to parameter 'str' here
 */
void remove_digits(char *str, size_t len) {
    int i, j = 0;
    for (i = 0; i < len; i++) {
        if (!isdigit((unsigned char)str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *  excess elements in 'char[]' initializer
     *  (near initialization for 'strings')
     */
    char strings[] = {"123abc456", "789def012", "345ghi678"};
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    for (int i = 0; i < num_strings; i++) {
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion passing 'char' to parameter of type 'const char *'; take the address with & [-Wint-conversion]
         *  passing argument 1 of 'strlen' makes pointer from integer without a cast [-Wint-conversion]
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t str_len = strlen(strings[i]);
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion passing 'char' to parameter of type 'char *'; take the address with & [-Wint-conversion]
         *  possible fix: take the address with '&'
         *  passing argument 1 of 'remove_digits' makes pointer from integer without a cast [-Wint-conversion]
         */
        remove_digits(strings[i], str_len);
        printf("%s\n", strings[i]);
    }

    return 0;
}