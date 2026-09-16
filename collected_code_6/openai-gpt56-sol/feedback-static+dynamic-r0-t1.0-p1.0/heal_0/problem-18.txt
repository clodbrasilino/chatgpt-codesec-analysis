#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_characters(char *string, const char *characters)
{
    unsigned char remove_table[256] = {0};
    char *source;
    char *destination;

    for (; *characters != '\0'; ++characters) {
        remove_table[(unsigned char)*characters] = 1;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        if (remove_table[(unsigned char)*source] == 0) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_capacity = 0;
    size_t second_capacity = 0;
    ssize_t first_length;
    ssize_t second_length;

    first_length = getline(&first, &first_capacity, stdin);
    if (first_length < 0) {
        free(first);
        return EXIT_FAILURE;
    }

    second_length = getline(&second, &second_capacity, stdin);
    if (second_length < 0) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    if (first_length > 0 && first[first_length - 1] == '\n') {
        first[first_length - 1] = '\0';
    }

    if (second_length > 0 && second[second_length - 1] == '\n') {
        second[second_length - 1] = '\0';
    }

    remove_characters(first, second);

    if (printf("%s\n", first) < 0) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    free(first);
    free(second);

    return EXIT_SUCCESS;
}