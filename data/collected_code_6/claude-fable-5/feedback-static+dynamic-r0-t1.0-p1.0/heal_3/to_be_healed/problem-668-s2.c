#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256U

void squeeze_char(char *str, size_t max_len, char ch);

void squeeze_char(char *str, size_t max_len, char ch)
{
    size_t read_idx;
    size_t write_idx;
    size_t len;

    if ((str == NULL) || (max_len == 0U)) {
        return;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        str[max_len - 1U] = '\0';
        len = max_len - 1U;
    }

    write_idx = 0U;

    for (read_idx = 0U; read_idx < len; read_idx++) {
        if ((str[read_idx] == ch) &&
            (read_idx > 0U) &&
            (str[read_idx - 1U] == ch)) {
            continue;
        }
        str[write_idx] = str[read_idx];
        write_idx++;
    }

    str[write_idx] = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char target;
    int input_char;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input string\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    } else if (len == (sizeof(buffer) - 1U)) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((input_char = getchar()) != EOF) {
            if (input_char == (int)'\n') {
                break;
            }
        }
    }

    printf("Enter character to squeeze: ");
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    input_char = getchar();
    if (input_char == EOF) {
        fprintf(stderr, "Error reading character\n");
        return EXIT_FAILURE;
    }

    target = (char)input_char;

    squeeze_char(buffer, sizeof(buffer), target);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}