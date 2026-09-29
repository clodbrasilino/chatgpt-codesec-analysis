#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256U

void remove_first_last(char *str, size_t max_len, char ch)
{
    size_t len;
    char *first;
    char *last;
    size_t tail_len;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, max_len);
    if (len == 0U || len >= max_len) {
        if (len >= max_len) {
            str[max_len - 1U] = '\0';
            len = max_len - 1U;
        }
        if (len == 0U) {
            return;
        }
    }

    first = memchr(str, (int)ch, len);
    if (first == NULL) {
        return;
    }

    last = NULL;
    {
        size_t i;
        for (i = len; i > 0U; i--) {
            if (str[i - 1U] == ch) {
                last = &str[i - 1U];
                break;
            }
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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char ch;
    int c;

    printf("Enter a string: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input string\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

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

    remove_first_last(buffer, sizeof(buffer), ch);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}