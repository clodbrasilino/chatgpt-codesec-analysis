#include <stdio.h>
#include <stdlib.h>

void remove_spaces(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return;
    }

    char *dst = str;
    char *src = str;
    /* Possible weaknesses found:
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     */
    char *end = str + len;

    while (*src != '\0' && src < end) {
        if (*src != ' ') {
            if (dst < end) {
                *dst = *src;
                dst++;
            }
        }
        src++;
    }
    
    if (dst < end) {
        *dst = '\0';
    } else {
        str[len - 1] = '\0';
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    remove_spaces(buffer, sizeof(buffer));

    if (fputs(buffer, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}