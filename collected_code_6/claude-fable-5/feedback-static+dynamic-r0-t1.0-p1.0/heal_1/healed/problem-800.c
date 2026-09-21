#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

void remove_whitespace(char *str)
{
    size_t read;
    size_t write;

    if (str == NULL) {
        return;
    }

    read = 0;
    write = 0;

    while (str[read] != '\0') {
        if (!isspace((unsigned char)str[read])) {
            str[write] = str[read];
            write++;
        }
        read++;
    }
    str[write] = '\0';
}

int main(void)
{
    char text[] = "  Hello,   World! \t This is a\ntest.  ";

    printf("Before: \"%s\"\n", text);
    remove_whitespace(text);
    printf("After:  \"%s\"\n", text);

    return 0;
}