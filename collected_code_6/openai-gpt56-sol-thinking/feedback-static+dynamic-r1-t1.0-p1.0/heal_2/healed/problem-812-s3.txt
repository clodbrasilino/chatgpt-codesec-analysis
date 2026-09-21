#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_word_character(unsigned char character)
{
    return isalnum(character) || character == '_';
}

static int abbreviate_road(char *text)
{
    char *read_position;
    char *write_position;

    if (text == NULL) {
        return -1;
    }

    read_position = text;
    write_position = text;

    while (*read_position != '\0') {
        int starts_word = read_position == text ||
                          !is_word_character((unsigned char)read_position[-1]);

        if (starts_word &&
            strncmp(read_position, "road", 4) == 0 &&
            !is_word_character((unsigned char)read_position[4])) {
            *write_position++ = 'r';
            *write_position++ = 'd';
            *write_position++ = '.';
            read_position += 4;
        } else {
            *write_position++ = *read_position++;
        }
    }

    *write_position = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        if (fprintf(stderr, "Usage: %s \"text\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (abbreviate_road(argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}