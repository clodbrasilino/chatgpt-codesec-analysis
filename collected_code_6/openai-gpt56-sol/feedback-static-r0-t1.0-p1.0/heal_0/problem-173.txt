#include <ctype.h>
#include <stdio.h>

void remove_non_alphanumeric(char *str)
{
    if (str == NULL) {
        return;
    }

    size_t read_index = 0;
    size_t write_index = 0;

    while (str[read_index] != '\0') {
        unsigned char ch = (unsigned char)str[read_index];

        if (isalnum(ch) != 0) {
            str[write_index++] = str[read_index];
        }

        ++read_index;
    }

    str[write_index] = '\0';
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    remove_non_alphanumeric(input);

    if (puts(input) == EOF) {
        return 1;
    }

    return 0;
}