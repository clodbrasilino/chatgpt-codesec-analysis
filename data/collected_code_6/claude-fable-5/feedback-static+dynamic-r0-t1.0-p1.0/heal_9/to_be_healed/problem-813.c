#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'printf' is defined in header '<stdio.h>'; this is probably fixable by adding '#include <stdio.h>'
  */

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
 *  expected ';' after top level declarator
 *  type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
 *  expected '=', ',', ';', 'asm' or '__attribute__' before ':' token
 */
**Analysis:**

/* Possible weaknesses found:
 *  expected ';' after top level declarator
 *  stray '`' in program
 * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
 *  type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
 */
The original code is already well-hardened against the Flawfinder warning (CWE-119/CWE-120). The rewrite preserves the code as-is because every access to the statically-sized `buffer` is properly bounds-checked:

/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  The code contains unhandled character(s) (character code=226). Neither unicode nor extended ascii is supported. [syntaxError]
 *  stray '`' in program
 *  stray '\342' in program
 */
1. **Argument copy loop** — bounded by `sizeof(buffer) - 1`, guaranteeing room for the null terminator, which is explicitly written after the loop. This prevents overflow regardless of `argv[1]` length.

/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '`' in program
 *  stray '\342' in program
 */
2. **`fgets` usage** — the size argument `(int)sizeof(buffer)` limits input to the buffer capacity, and the defensive `buffer[sizeof(buffer) - 1] = '\0'` guarantees termination even in edge cases.

/* Possible weaknesses found:
 *  unexpected character <U+2014>
 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
 *  stray '`' in program
 *  stray '\342' in program
 */
3. **Newline-stripping loop** — bounded by `sizeof(buffer)`, so it can never read past the array even if termination were somehow missing.

/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '`' in program
 *  stray '\342' in program
 */
4. **`string_length`** — handles `NULL` safely and only ever reads up to the terminator, which is guaranteed to exist by the earlier logic.

/* Possible weaknesses found:
 *  unexpected character <U+2014>
 * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. (risk 4, buffer)
 *  unknown type name 'printf'
 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
 *  expected identifier or '('
 * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. (risk 4, buffer)
 *  stray '`' in program
 * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
 * Flawfinder gets: Does not check for buffer overflows (CWE-120, CWE-20). Use fgets() instead. (risk 5, buffer)
 *  stray '\342' in program
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'a'
 *  unknown type name 'a'
 */
5. **No unsafe functions** — no `strcpy`, `gets`, `sprintf`, or unbounded `scanf` are used; `printf` uses a constant format string, avoiding format-string vulnerabilities (CWE-134).

/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '`' in program
 *  stray '\342' in program
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
The Flawfinder hit on `char buffer[MAX_INPUT]` is a heuristic flag on any statically-sized array — the recommended mitigations (bounds checking, length-limiting functions) are already fully implemented, so no functional changes were required.