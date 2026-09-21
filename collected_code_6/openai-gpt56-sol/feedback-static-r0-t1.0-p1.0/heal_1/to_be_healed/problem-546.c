#include <stdio.h>
#include <stddef.h>

const char *find_last_char(const char *string, int character)
{
    const char *last = NULL;
    unsigned char target = (unsigned char)character;

    if (string == NULL) {
        return NULL;
    }

    do {
        if ((unsigned char)*string == target) {
            last = string;
        }
    } while (*string++ != '\0');

    return last;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[1024];
    int character;
    const char *result;

    if (fgets(string, sizeof string, stdin) == NULL) {
        return 1;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        if (string[i] == '\n') {
            string[i] = '\0';
            break;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = getchar();
    if (character == EOF) {
        return 1;
    }

    result = find_last_char(string, character);
    if (result == NULL) {
        puts("Character not found");
    } else {
        printf("%td\n", result - string);
    }

    return 0;
}