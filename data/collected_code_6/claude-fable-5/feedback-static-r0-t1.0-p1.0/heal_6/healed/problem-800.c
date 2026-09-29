#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

void remove_whitespace(char *str, size_t max_len)
{
    size_t read;
    size_t write;

    if (str == NULL || max_len == 0) {
        return;
    }

    read = 0;
    write = 0;

    while (read < max_len && str[read] != '\0') {
        if (!isspace((unsigned char)str[read])) {
            str[write] = str[read];
            write++;
        }
        read++;
    }

    if (write < max_len) {
        str[write] = '\0';
    } else {
        str[max_len - 1] = '\0';
    }
}

int main(void)
{
    char text[] = "  Hello,   World! \t This is a\ntest.  ";

    printf("Before: \"%s\"\n", text);
    remove_whitespace(text, sizeof(text));
    printf("After:  \"%s\"\n", text);

    return 0;
}