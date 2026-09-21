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
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(void)
{
    char buffer[256];
    char ch;
    int c;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input string\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        flush_stdin();
    }

    printf("Enter a character to remove: ");
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