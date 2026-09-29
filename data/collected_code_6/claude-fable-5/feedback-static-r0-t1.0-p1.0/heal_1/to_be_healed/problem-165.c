#include <stdio.h>
#include <string.h>
#include <stddef.h>

size_t count_position_matches(const char *str)
{
    size_t count = 0;
    size_t len;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    for (i = 0; i < len; i++) {
        if (i < 26) {
            char c = str[i];
            if (c == (char)('a' + i) || c == (char)('A' + i)) {
                count++;
            }
        } else {
            break;
        }
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t result;
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
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = count_position_matches(buffer);

    printf("Characters at same position as in alphabet: %zu\n", result);

    return 0;
}