#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void remove_whitespace(char *str)
{
    size_t read_index = 0;
    size_t write_index = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_index] != '\0') {
        if (!isspace((unsigned char)str[read_index])) {
            str[write_index] = str[read_index];
            write_index++;
        }
        read_index++;
    }

    str[write_index] = '\0';
}

int main(void)
{
    char text[] = "  Hello,   World!  \t This is a \n test.  ";

    printf("Before: \"%s\"\n", text);

    remove_whitespace(text);

    printf("After:  \"%s\"\n", text);

    return EXIT_SUCCESS;
}