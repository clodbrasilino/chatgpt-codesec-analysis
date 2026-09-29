#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256U
#define FLUSH_LIMIT 4096U

static void remove_first_last(char *str, size_t max_len, char ch)
{
    size_t len;
    char *first;
    char *last;
    size_t tail_len;
    size_t i;

    if (str == NULL || max_len == 0U) {
        return;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        str[max_len - 1U] = '\0';
        len = max_len - 1U;
    }
    if (len == 0U) {
        return;
    }

    first = memchr(str, (int)(unsigned char)ch, len);
    if (first == NULL) {
        return;
    }

    last = NULL;
    for (i = len; i > 0U; i--) {
        if (str[i - 1U] == ch) {
            last = &str[i - 1U];
            break;
        }
    }

    if (last != NULL && last != first) {
        tail_len = len - (size_t)(last - str) - 1U;
        memmove(last, last + 1, tail_len + 1U);
        len -= 1U;
    }

    tail_len = len - (size_t)(first - str) - 1U;
    memmove(first, first + 1, tail_len + 1U);
}

static void flush_input(void)
{
    int c;
    size_t count = 0U;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        count++;
    } while (c != '\n' && c != EOF && count < FLUSH_LIMIT);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char ch;
    int c;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input string\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strcspn(buffer, "\n");
    if (len == strnlen(buffer, sizeof(buffer)) && len == sizeof(buffer) - 1U) {
        flush_input();
    }
    buffer[len] = '\0';

    printf("Enter a character to remove: ");
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error reading character\n");
        return EXIT_FAILURE;
    }
    ch = (char)c;

    if (c != '\n') {
        flush_input();
    }

    remove_first_last(buffer, sizeof(buffer), ch);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}