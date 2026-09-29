#include <stdio.h>
#include <stdlib.h>

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
    int read_result;

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    read_result = scanf("%255s", buffer);
    if (read_result != 1) {
        return EXIT_FAILURE;
    }

    replace_spaces(buffer, '_');
    printf("%s\n", buffer);

    return EXIT_SUCCESS;
}