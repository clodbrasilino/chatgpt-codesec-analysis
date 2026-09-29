#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary = string[begin];
        string[begin] = string[end];
        string[end] = temporary;
        ++begin;
        --end;
    }
}

static int left_rotate(char *string, size_t positions)
{
    size_t length;

    if (string == NULL) {
        return -1;
    }

    length = strlen(string);
    if (length == 0U) {
        return 0;
    }

    positions %= length;
    if (positions == 0U) {
        return 0;
    }

    reverse_range(string, 0U, positions - 1U);
    reverse_range(string, positions, length - 1U);
    reverse_range(string, 0U, length - 1U);

    return 0;
}

int main(void)
{
    char input[1024];
    char rotation_text[64];
    char *end = NULL;
    unsigned long long parsed_rotation;
    size_t rotation;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\n");
    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        return EXIT_FAILURE;
    }

    if (fgets(rotation_text, sizeof rotation_text, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    parsed_rotation = strtoull(rotation_text, &end, 10);
    if (end == rotation_text) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0' || parsed_rotation > (unsigned long long)SIZE_MAX) {
        return EXIT_FAILURE;
    }

    rotation = (size_t)parsed_rotation;

    if (left_rotate(input, rotation) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}