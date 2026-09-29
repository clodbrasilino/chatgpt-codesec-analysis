#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int max_occurring_char(const char *str, char *result)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t i;
    unsigned char best = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    if (str[0] == '\0') {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
            best = c;
        }
    }

    *result = (char)best;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char max_char = '\0';
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    if (max_occurring_char(buffer, &max_char) != 0) {
        fprintf(stderr, "Invalid or empty input\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum occurring character: %c\n", max_char) < 0) {
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

The original code already addresses the Flawfinder warning (CWE-119/CWE-120) correctly, so the rewrite preserves the existing mitigations:

/* Possible weaknesses found:
 *  stray '\342' in program
 *  stray '`' in program
 *  unexpected character <U+2014>
 *  The code contains unhandled character(s) (character code=226). Neither unicode nor extended ascii is supported. [syntaxError]
 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
 */
1. **Bounded input reading** — `fgets(buffer, (int)sizeof(buffer), stdin)` limits the read to the buffer size, preventing overflow of the statically-sized array.
/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '\342' in program
 *  stray '`' in program
 */
2. **Guaranteed null termination** — `buffer[sizeof(buffer) - 1] = '\0'` is defensive (though `fgets` already null-terminates), and `memset` zero-initializes the buffer.
/* Possible weaknesses found:
 *  stray '\342' in program
 *  stray '`' in program
 *  unexpected character <U+2014>
 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
 */
3. **Bounded length calculation** — `strnlen` with `sizeof(buffer)` is used instead of `strlen`, avoiding a read past the buffer even if termination somehow failed.
/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '\342' in program
 *  stray '`' in program
 */
4. **Safe indexing in the counting logic** — casting to `unsigned char` before indexing `counts[UCHAR_MAX + 1]` prevents negative-index undefined behavior on platforms where `char` is signed.
/* Possible weaknesses found:
 * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
 *  unexpected character <U+2014>
 *  stray '\342' in program
 *  stray '`' in program
 */
5. **NULL and empty-string checks** — `max_occurring_char` validates both pointers and rejects empty input, with all error paths checked (`fgets`, `printf` return values).

/* Possible weaknesses found:
 *  expected ';' after top level declarator
 *  unknown type name 'the'
 * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
 *  expected '=', ',', ';', 'asm' or '__attribute__' before '-' token
 */
No functional changes were required; the statically-sized buffer is safe because every access is bounds-limited.