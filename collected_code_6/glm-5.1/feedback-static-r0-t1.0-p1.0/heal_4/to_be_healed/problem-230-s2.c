#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_spaces(char *str, char ch) {
    if (str == NULL) {
        return;
    }
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            str[i] = ch;
        }
        i++;
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

    buffer[strcspn(buffer, "\n")] = '\0';

    replace_spaces(buffer, '_');
    printf("%s\n", buffer);

    return EXIT_SUCCESS;
}