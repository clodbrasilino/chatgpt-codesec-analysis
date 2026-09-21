#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 256

void remove_multiple_spaces(char *str)
{
    size_t read_index = 0;
    size_t write_index = 0;
    int previous_was_space = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_index] != '\0') {
        if (str[read_index] == ' ') {
            if (previous_was_space == 0) {
                str[write_index] = str[read_index];
                write_index++;
            }
            previous_was_space = 1;
        } else {
            str[write_index] = str[read_index];
            write_index++;
            previous_was_space = 0;
        }
        read_index++;
    }

    str[write_index] = '\0';
}

int main(void)
{
    char input[] = "This   is  a    string   with     multiple spaces";
    char *buffer = NULL;
    size_t input_length = 0;
    size_t buffer_size = 0;

    input_length = strnlen(input, MAX_INPUT_SIZE - 1);
    buffer_size = input_length + 1;

    if (buffer_size > MAX_INPUT_SIZE) {
        fprintf(stderr, "Input exceeds maximum allowed size\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (input_length >= buffer_size) {
        fprintf(stderr, "Copy size exceeds destination buffer\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, input_length);
    buffer[input_length] = '\0';

    printf("Before: \"%s\"\n", buffer);
    remove_multiple_spaces(buffer);
    printf("After:  \"%s\"\n", buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}

/* Possible weaknesses found:
 *  type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
 *  expected ';' after top level declarator
 *  stray '`' in program
 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'of'
 *  unknown type name 'of'
 */
**Analysis of the flagged weakness (CWE-120, `memcpy`):**

/* Possible weaknesses found:
 *  stray '`' in program
 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
 */
The Flawfinder warning on `memcpy` is a heuristic hit rather than an actual vulnerability in this code, and the existing mitigations are already correct:

/* Possible weaknesses found:
 *  stray '`' in program
 *  syntax error [syntaxError]
 */
1. **Bounded length measurement:** `strnlen(input, MAX_INPUT_SIZE - 1)` guarantees `input_length` can never exceed `MAX_INPUT_SIZE - 1`, even if `input` were somehow unterminated.
/* Possible weaknesses found:
 *  stray '`' in program
 */
2. **Destination sized from source:** `buffer_size = input_length + 1` ensures the destination is allocated to exactly fit the copied bytes plus the NUL terminator.
/* Possible weaknesses found:
 *  stray '`' in program
 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
 */
3. **Explicit pre-copy guard:** The `input_length >= buffer_size` check verifies the destination can hold the source data before `memcpy` executes, which is precisely what CWE-120 asks for.
/* Possible weaknesses found:
 *  stray '`' in program
 */
4. **Manual NUL termination:** `buffer[input_length] = '\0'` guarantees the buffer is a valid C string regardless of the copy contents.
/* Possible weaknesses found:
 *  stray '`' in program
 */
5. **Allocation failure handling and cleanup:** `malloc` is checked, `free` is called on all exit paths after allocation, and the pointer is nulled after freeing to prevent accidental use-after-free.

Since the destination size is provably sufficient at the point of the copy, the code is retained as-is with the audit comment removed, per your instructions.