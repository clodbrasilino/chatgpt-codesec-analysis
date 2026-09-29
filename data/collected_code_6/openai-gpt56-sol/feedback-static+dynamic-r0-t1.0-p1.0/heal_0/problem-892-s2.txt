#include <stdio.h>

void remove_multiple_spaces(char *str)
{
    char *read;
    char *write;
    int previous_was_space = 0;

    if (str == NULL) {
        return;
    }

    read = str;
    write = str;

    while (*read != '\0') {
        if (*read == ' ') {
            if (!previous_was_space) {
                *write++ = *read;
                previous_was_space = 1;
            }
        } else {
            *write++ = *read;
            previous_was_space = 0;
        }
        read++;
    }

    *write = '\0';
}

int main(void)
{
    char text[1024];

    if (fgets(text, sizeof(text), stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    remove_multiple_spaces(text);

    if (fputs(text, stdout) == EOF) {
        return 1;
    }

    return 0;
}