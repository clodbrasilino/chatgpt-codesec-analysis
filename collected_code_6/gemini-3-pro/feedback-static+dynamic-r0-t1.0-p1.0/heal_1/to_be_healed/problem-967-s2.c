#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool contains_all_vowels(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool found_a = false;
    bool found_e = false;
    bool found_i = false;
    bool found_o = false;
    bool found_u = false;

    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = tolower((unsigned char)str[i]);
        if (c == 'a') found_a = true;
        else if (c == 'e') found_e = true;
        else if (c == 'i') found_i = true;
        else if (c == 'o') found_o = true;
        else if (c == 'u') found_u = true;

        if (found_a && found_e && found_i && found_o && found_u) {
            return true;
        }
    }

    return false;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (contains_all_vowels(buffer)) {
            printf("Accepted\n");
        } else {
            printf("Rejected\n");
        }
    }

    return 0;
}