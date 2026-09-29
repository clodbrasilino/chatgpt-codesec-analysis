#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void remove_first_last(char *str, size_t max_size, char ch)
{
    size_t len;
    char *first;
    char *last;
    size_t pos;

    if (str == NULL || max_size == 0) {
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

    last = strrchr(str, ch);

    if (last != NULL && last != first) {
        pos = (size_t)(last - str);
        memmove(str + pos, str + pos + 1, len - pos);
        len--;
    }

    pos = (size_t)(first - str);
    memmove(str + pos, str + pos + 1, len - pos);
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char ch;
    int c;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input string\n");
        return 1;
    }
    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        while ((c = getchar()) != EOF && c != '\n') {
            ;
        }
    }

    printf("Enter a character to remove: ");
    c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error reading character\n");
        return 1;
    }
    ch = (char)c;

    remove_first_last(buffer, sizeof(buffer), ch);

    printf("Result: %s\n", buffer);

    return 0;
}