#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_chars(char *str) {
    if (str == NULL) {
        return;
    }
    while (*str != '\0') {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
        }
        str++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    replace_chars(buffer);
    printf("%s\n", buffer);
    return 0;
}