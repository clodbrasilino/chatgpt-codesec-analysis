#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 256

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i = 0;

    while (i < max_len && str[i] != '\0') {
        i++;
    }

    return i;
}

void toggle_case(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return;
    }

    len = bounded_strlen(str, max_len);
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
    char buffer[MAX_INPUT_SIZE];

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
 *  expected ';' after top level declarator
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'weakness'
 *  unknown type name 'The'
 *  No pair for character ('). Can't process file. File is either invalid or unicode, which is currently not supported. [syntaxError]
 *  missing terminating ' character
 */
The identified weakness (CWE-119/CWE-120, statically-sized buffer) was already properly mitigated in the original code, so the logic remains unchanged. Here's why the code is safe:

/* Possible weaknesses found:
 *  unexpected character <U+2014>
 *  stray '\342' in program
 *  stray '`' in program
 */
1. **Bounded input reading**: `fgets(buffer, (int)sizeof(buffer), stdin)` limits input to the buffer size, preventing overflow on read — unlike unsafe alternatives such as `gets()` or unbounded `scanf("%s", ...)`.

/* Possible weaknesses found:
 *  unknown type name 'defensive'
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'defensive'
 *  expected identifier or '('
 *  stray '`' in program
 *  unknown type name 'is'
 */
2. **Guaranteed null termination**: `buffer[sizeof(buffer) - 1] = '\0';` is a defensive belt-and-suspenders measure (fgets already null-terminates on success, but this protects against future refactoring).

/* Possible weaknesses found:
 *  stray '`' in program
 */
3. **Bounded string length**: `bounded_strlen()` never reads past `max_len`, so even a non-terminated buffer cannot cause an out-of-bounds read in `toggle_case()`.

/* Possible weaknesses found:
 *  stray '`' in program
 */
4. **NULL and zero-length guards**: `toggle_case()` validates its arguments before use.

/* Possible weaknesses found:
 *  unexpected character <U+2265>
 *  stray '\342' in program
 *  stray '`' in program
 */
5. **Correct `ctype.h` usage**: characters are cast to `unsigned char` before being passed to `isupper()`/`islower()`/`toupper()`/`tolower()`, avoiding undefined behavior with negative `char` values (e.g., on platforms where `char` is signed and input contains bytes ≥ 0x80).

/* Possible weaknesses found:
 *  stray '`' in program
 */
6. **Newline stripping via `strcspn`**: safe even when no newline is present, since `strcspn` returns the index of the terminating null in that case.

/* Possible weaknesses found:
 *  expected ';' after top level declarator
 *  unknown type name 'are'
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'are'
 *  unknown type name 'all'
 */
The Flawfinder hit is a low-risk (risk 2) heuristic warning triggered merely by the presence of a fixed-size array; all accesses are properly bounds-checked, so no code changes were required beyond removing comments as requested.