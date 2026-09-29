#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_binary_string(const char *str)
{
    size_t i;

    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return false;
    }

    for (i = 0U; str[i] != '\0'; i++) {
        if ((str[i] != '0') && (str[i] != '1')) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t len;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    if (is_binary_string(buffer)) {
        printf("The string is a binary string\n");
    } else {
        printf("The string is not a binary string\n");
    }

    return 0;
}