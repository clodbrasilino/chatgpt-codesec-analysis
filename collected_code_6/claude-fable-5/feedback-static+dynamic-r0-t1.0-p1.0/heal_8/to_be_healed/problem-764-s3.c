#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

size_t count_numeric(const char *str)
{
    size_t count;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    count = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    result = count_numeric(buffer);

    if (printf("Numeric characters: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* Possible weaknesses found:
 *  expected ';' after top level declarator
 *  type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'notes'
 */
**Analysis notes:**

/* Possible weaknesses found:
 *  stray '`' in program
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
The Flawfinder warning on the statically-sized `char buffer[BUFFER_SIZE]` array (CWE-119/CWE-120) is already properly mitigated in this code, so no functional changes were required:

/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  The code contains unhandled character(s) (character code=226). Neither unicode nor extended ascii is supported. [syntaxError]
 * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. (risk 4, buffer)
 *  stray '`' in program
 * Flawfinder gets: Does not check for buffer overflows (CWE-120, CWE-20). Use fgets() instead. (risk 5, buffer)
 *  stray '\342' in program
 */
1. **Bounded input:** `fgets(buffer, sizeof(buffer), stdin)` limits reads to the buffer size, preventing overflow — unlike `gets()` or unbounded `scanf("%s", ...)`.
/* Possible weaknesses found:
 *  stray '`' in program
 */
2. **Guaranteed termination:** `buffer[sizeof(buffer) - 1] = '\0'` is defensive (technically redundant since `fgets` always null-terminates on success, but harmless and explicit).
/* Possible weaknesses found:
 *  stray '`' in program
 */
3. **Newline stripping:** `strcspn(buffer, "\n")` safely removes the trailing newline, and works correctly even when no newline is present (it returns the index of the existing null terminator).
/* Possible weaknesses found:
 *  hexadecimal floating constants require an exponent
 *  stray '`' in program
 *  stray '\342' in program
 *  unexpected character <U+2265>
 */
4. **Safe character classification:** the `(unsigned char)` cast before `isdigit()` avoids undefined behavior on platforms where `char` is signed and the input contains bytes ≥ 0x80.
/* Possible weaknesses found:
 *  stray '`' in program
 * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
 */
5. **NULL guard:** `count_numeric()` handles a NULL pointer, and both `fgets` and `printf` return values are checked.

/* Possible weaknesses found:
 *  unknown type name 'the'
 *  unknown type name 'code'
 *  expected ';' after top level declarator
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'code'
 */
The warning is a low-risk (risk 2) static-analysis heuristic triggered merely by the presence of a fixed-size buffer; the surrounding code already performs the recommended bounds checking.