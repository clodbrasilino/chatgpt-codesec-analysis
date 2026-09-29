#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void squeeze_char(char *str, char ch);

void squeeze_char(char *str, char ch)
{
    size_t read_idx;
    size_t write_idx;
    size_t len;

    if (str == NULL) {
        return;
    }

    len = strlen(str);
    write_idx = 0U;

    for (read_idx = 0U; read_idx < len; read_idx++) {
        if ((str[read_idx] == ch) &&
            (read_idx > 0U) &&
            (str[read_idx - 1U] == ch)) {
            continue;
        }
        str[write_idx] = str[read_idx];
        write_idx++;
    }

    str[write_idx] = '\0';
}

int main(void)
{
    char buffer[256];
    char target;
    int input_char;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input string\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    printf("Enter character to squeeze: ");
    input_char = getchar();
    if (input_char == EOF) {
        fprintf(stderr, "Error reading character\n");
        return EXIT_FAILURE;
    }

    target = (char)input_char;

    squeeze_char(buffer, target);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}