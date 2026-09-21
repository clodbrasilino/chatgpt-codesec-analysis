#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256
#define CHAR_INPUT_SIZE 8

static char *bounded_strrchr(char *str, size_t len, char ch)
{
    size_t i;

    if (str == NULL || len == 0) {
        return NULL;
    }

    i = len;
    while (i > 0) {
        i--;
        if (str[i] == ch) {
            return str + i;
        }
    }
    return NULL;
}

void remove_first_last(char *str, size_t max_size, char ch)
{
    size_t len;
    char *first;
    char *last;
    size_t pos;

    if (str == NULL || max_size == 0 || ch == '\0') {
        return;
    }

    len = strnlen(str, max_size);
    if (len == 0 || len >= max_size) {
        return;
    }

    first = memchr(str, (unsigned char)ch, len);
    if (first == NULL) {
        return;
    }

    last = bounded_strrchr(str, len, ch);

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
    size_t guard;

    guard = 0;
    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        guard++;
    } while (c != EOF && c != '\n' && guard < (size_t)-1);
}

static int read_line(char *buf, size_t size)
{
    size_t len;

    if (buf == NULL || size == 0) {
        return -1;
    }

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    buf[size - 1] = '\0';

    len = strnlen(buf, size);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
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
    char buffer[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char char_input[CHAR_INPUT_SIZE];
    char ch;

    printf("Enter a string: ");
    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading input string\n");
        return 1;
    }

    printf("Enter a character to remove: ");
    if (read_line(char_input, sizeof(char_input)) != 0) {
        fprintf(stderr, "Error reading character\n");
        return 1;
    }

    if (char_input[0] == '\0') {
        fprintf(stderr, "No character entered\n");
        return 1;
    }
    ch = char_input[0];

    remove_first_last(buffer, sizeof(buffer), ch);

    printf("Result: %s\n", buffer);

    return 0;
}