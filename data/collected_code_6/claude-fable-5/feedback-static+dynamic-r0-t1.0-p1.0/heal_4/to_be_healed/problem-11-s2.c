#include <stdio.h>
#include <string.h>

void remove_first_last(char *str, size_t max_len, char ch)
{
    size_t len;
    char *first;
    char *last;
    size_t pos;

    if (str == NULL || max_len == 0) {
        return;
    }

    str[max_len - 1] = '\0';

    len = strnlen(str, max_len);
    if (len == 0) {
        return;
    }

    first = memchr(str, ch, len);
    if (first == NULL) {
        return;
    }

    last = strrchr(str, ch);

    if (last != NULL && last != first) {
        pos = (size_t)(last - str);
        if (pos < len) {
            memmove(str + pos, str + pos + 1, len - pos);
            len--;
        }
    }

    pos = (size_t)(first - str);
    if (pos < len) {
        memmove(str + pos, str + pos + 1, len - pos);
    }
}

static void flush_stdin(void)
{
    int c;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    } while (c != '\n' && c != EOF);
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size == 0) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1] = '\0';

    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1) {
        flush_stdin();
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char ch;
    int c;

    printf("Enter a string: ");
    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading input string\n");
        return 1;
    }

    printf("Enter a character to remove: ");
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error reading character\n");
        return 1;
    }
    ch = (char)c;

    if (c != '\n') {
        flush_stdin();
    }

    remove_first_last(buffer, sizeof(buffer), ch);

    printf("Result: %s\n", buffer);

    return 0;
}