#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int length = 0;
    int last_length = 0;

    while (*s != '\0') {
        if (isspace((unsigned char)*s)) {
            if (length > 0) {
                last_length = length;
                length = 0;
            }
        } else {
            length++;
        }
        s++;
    }

    return length > 0 ? length : last_length;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[10240];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        printf("%d\n", lengthOfLastWord(buffer));
    }

    return 0;
}