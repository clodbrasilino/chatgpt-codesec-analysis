#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_digits(char *str) {
    char *src = str, *dst = str;
    /* Possible weaknesses found:
     * ASan: SEGV
     */
    while (*src) {
        if (!isdigit((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
    return str;
}

/* Possible weaknesses found:
 *  expected 'char **' but argument is of type 'char (*)[20]'
 */
void strip_list(char **list, int size) {
    for (int i = 0; i < size; ++i) {
        remove_digits(list[i]);
    }
}

int main() {
    char strings[][20] = {"hello123", "456world", "test789case", "no4digits"};
    int size = sizeof(strings) / sizeof(strings[0]);

    /* Possible weaknesses found:
     *  passing argument 1 of 'strip_list' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    strip_list(strings, size);

    for (int i = 0; i < size; ++i) {
        printf("%s\n", strings[i]);
    }

    return 0;
}