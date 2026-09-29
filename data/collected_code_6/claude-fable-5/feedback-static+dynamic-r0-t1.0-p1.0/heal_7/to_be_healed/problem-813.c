#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 256

size_t string_length(const char *str)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT];
    size_t length;
    size_t i;

    buffer[0] = '\0';

    if (argc > 1 && argv[1] != NULL) {
        for (i = 0; i < sizeof(buffer) - 1 && argv[1][i] != '\0'; i++) {
            buffer[i] = argv[1][i];
        }
        buffer[i] = '\0';
    } else {
        if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
            printf("0\n");
            fflush(stdout);
            return EXIT_SUCCESS;
        }
        buffer[sizeof(buffer) - 1] = '\0';
    }

    for (i = 0; i < sizeof(buffer) && buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\r') {
            buffer[i] = '\0';
            break;
        }
    }

    length = string_length(buffer);

    printf("%zu\n", length);
    fflush(stdout);

    return EXIT_SUCCESS;
}

/* Possible weaknesses found:
 * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. (risk 4, buffer)
 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
 *  syntax error: required .  [syntaxError]
 *  unknown type name 'The'
 *  expected ';' after top level declarator
 *  stray '`' in program
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'was'
 * Flawfinder gets: Does not check for buffer overflows (CWE-120, CWE-20). Use fgets() instead. (risk 5, buffer)
 *  unknown type name 'was'
 */
The code was already well-defended against the identified weakness. The Flawfinder warning about the statically-sized `buffer` array (CWE-119/CWE-120) is mitigated because every write into the buffer is bounds-checked: the argv copy loop is limited to `sizeof(buffer) - 1` and explicitly null-terminated, `fgets` is called with the exact buffer size so it cannot overflow, and a defensive null terminator is placed at the last index after reading from stdin. The newline-stripping loop is also bounded by `sizeof(buffer)`, and `string_length` guards against a NULL pointer. No unsafe functions like `strcpy`, `gets`, or `sprintf` are used, so no functional changes were required.