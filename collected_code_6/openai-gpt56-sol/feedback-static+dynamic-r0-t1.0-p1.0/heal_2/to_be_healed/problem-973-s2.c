#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary = string[begin];
        string[begin++] = string[end];
        string[end--] = temporary;
    }
}

static int left_rotate(char *string, size_t length, size_t positions)
{
    if (string == NULL) {
        return -1;
    }

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

static int read_line(char **line, size_t *length)
{
    char *buffer = NULL;
    size_t used = 0U;
    size_t capacity = 128U;
    int character;

    if (line == NULL || length == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (used == SIZE_MAX - 1U) {
            free(buffer);
            return -1;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return -1;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[used++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (character == EOF && used == 0U) {
        free(buffer);
        return 0;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *rotation_text = NULL;
    char *end = NULL;
    size_t input_length = 0U;
    size_t rotation_text_length = 0U;
    size_t rotation;
    uintmax_t parsed_rotation;
    int status;

    status = read_line(&input, &input_length);
    if (status != 1) {
        free(input);
        return EXIT_FAILURE;
    }

    status = read_line(&rotation_text, &rotation_text_length);
    if (status != 1) {
        free(input);
        free(rotation_text);
        return EXIT_FAILURE;
    }

    errno = 0;
    /* Possible weaknesses found:
     *  call to undeclared function 'strtoumax'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strtoumax'; did you mean 'strtouq'? [-Wimplicit-function-declaration]
     */
    parsed_rotation = strtoumax(rotation_text, &end, 10);

    if (end == rotation_text || errno == ERANGE) {
        free(input);
        free(rotation_text);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0' || parsed_rotation > SIZE_MAX) {
        free(input);
        free(rotation_text);
        return EXIT_FAILURE;
    }

    rotation = (size_t)parsed_rotation;

    if (left_rotate(input, input_length, rotation) != 0 ||
        puts(input) == EOF) {
        free(input);
        free(rotation_text);
        return EXIT_FAILURE;
    }

    free(input);
    free(rotation_text);
    return EXIT_SUCCESS;
}