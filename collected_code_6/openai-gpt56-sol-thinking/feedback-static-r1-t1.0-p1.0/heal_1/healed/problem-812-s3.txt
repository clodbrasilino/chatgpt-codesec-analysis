#include <ctype.h>
#include <stdint.h>
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
            memcpy(write_position, "rd.", 3);
            write_position += 3;
            read_position += 4;
        } else {
            *write_position++ = *read_position++;
        }
    }

    *write_position = '\0';
    return 0;
}

int main(int argc, char *const argv[])
{
    const char *program_name;
    char *text;
    size_t length;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s \"text\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);
    if (length == SIZE_MAX) {
        return EXIT_FAILURE;
    }

    text = malloc(length + 1);
    if (text == NULL) {
        return EXIT_FAILURE;
    }

    memcpy(text, argv[1], length + 1);

    if (abbreviate_road(text) != 0) {
        free(text);
        return EXIT_FAILURE;
    }

    if (puts(text) == EOF) {
        free(text);
        return EXIT_FAILURE;
    }

    free(text);
    return EXIT_SUCCESS;
}