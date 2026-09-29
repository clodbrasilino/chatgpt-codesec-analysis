#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_chars(char *str1, const char *str2) {
    size_t len = 0;
    while (str1[len] != '\0') {
        if (strchr(str2, str1[len]) == NULL) {
            len++;
        } else {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memmove(&str1[len], &str1[len + 1], strlen(str1 + len) - (len == 0 ? 0 : 1));
        }
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[100] = "Hello, World!";
    const char *str2 = ",!";

    remove_chars(str1, str2);
    printf("%s\n", str1);

    return 0;
}