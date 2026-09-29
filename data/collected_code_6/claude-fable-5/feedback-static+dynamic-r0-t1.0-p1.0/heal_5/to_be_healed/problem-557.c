#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

void toggle_case(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return;
    }

    len = strnlen(str, max_len);
    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isupper(c)) {
            str[i] = (char)tolower(c);
        } else if (islower(c)) {
            str[i] = (char)toupper(c);
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    toggle_case(buffer, sizeof(buffer));

    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* Possible weaknesses found:
 *  missing terminating ' character
 *  unknown type name 'The'
 *  expected ';' after top level declarator
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'was'
 *  No pair for character ('). Can't process file. File is either invalid or unicode, which is currently not supported. [syntaxError]
 *  unknown type name 'was'
 */
The code was already well-hardened against the Flawfinder warning (CWE-119/CWE-120). Here's my analysis of why the existing mitigations are sound, and the small improvements I made:

**Existing mitigations that were kept:**

/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '`' in program
 *  stray '\342' in program
 */
1. **`fgets(buffer, sizeof(buffer), stdin)`** — bounded read that can never overflow the statically-sized array, unlike `gets()` or unbounded `scanf("%s")`.
/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '`' in program
 *  stray '\342' in program
 */
2. **`buffer[sizeof(buffer) - 1] = '\0'`** — defensive null termination (technically redundant after `fgets`, but harmless belt-and-suspenders).
/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '`' in program
 *  stray '\342' in program
 */
3. **`strcspn(buffer, "\n")`** — safe newline stripping that works correctly even when no newline is present (points at the existing terminator), avoiding the classic `buffer[strlen(buffer)-1]` underflow bug on empty input.
/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '`' in program
 *  stray '\342' in program
 */
4. **`strnlen(str, max_len)`** in `toggle_case` — bounded length calculation, so the function is safe even if passed a non-terminated buffer.
/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '`' in program
 *  stray '\342' in program
 */
5. **`(unsigned char)` casts before `isupper`/`islower`/`toupper`/`tolower`** — avoids undefined behavior when `char` is signed and holds negative values (e.g., high-bit characters from input).
/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '`' in program
 *  stray '\342' in program
 */
6. **`memset` initialization** — guarantees the buffer starts zeroed.
/* Possible weaknesses found:
 *  stray '`' in program
 */
7. **Checked return values** on `fgets` and `printf`.

**Minor improvements added:**

/* Possible weaknesses found:
 *  stray '`' in program
 */
- Added a `max_len == 0` guard in `toggle_case` for full defensive coverage.
/* Possible weaknesses found:
 *  stray '`' in program
 */
- Explicit `(int)` cast on the `fgets` size argument to document the intentional `size_t`-to-`int` conversion (safe here since `BUFFER_SIZE` is 256).

/* Possible weaknesses found:
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'satisfies'
 *  unknown type name 'the'
 *  expected ';' after top level declarator
 *  unknown type name 'satisfies'
 */
The Flawfinder hit is a low-risk (level 2) informational flag on any fixed-size buffer; the code satisfies its remediation advice by consistently using length-limited functions and bounds checking throughout.