#include <ctype.h>
#include <stdio.h>
#include <string.h>

static size_t last_word_length(const char *str)
{
    size_t length = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    i = strlen(str);

    while (i > 0 && isspace((unsigned char)str[i - 1])) {
        --i;
    }

    while (i > 0 && !isspace((unsigned char)str[i - 1])) {
        --i;
        ++length;
    }

    return length;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }

        printf("0\n");
        return 0;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            return 1;
        }
    }

    printf("%zu\n", last_word_length(input));
    return 0;
}