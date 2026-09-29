#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKEN_LENGTH ((size_t)1048576)
#define INPUT_BUFFER_SIZE ((size_t)4096)

typedef struct {
    FILE *stream;
    unsigned char *buffer;
    size_t capacity;
    size_t position;
    size_t length;
} InputReader;

static int input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return -1;
    }

    reader->buffer = malloc(INPUT_BUFFER_SIZE);
    if (reader->buffer == NULL) {
        return -1;
    }

    reader->stream = stream;
    reader->capacity = INPUT_BUFFER_SIZE;
    reader->position = 0;
    reader->length = 0;

    return 0;
}

static void input_reader_destroy(InputReader *reader)
{
    if (reader == NULL) {
        return;
    }

    free(reader->buffer);
    reader->buffer = NULL;
    reader->stream = NULL;
    reader->capacity = 0;
    reader->position = 0;
    reader->length = 0;
}

static int read_character(InputReader *reader, unsigned char *character)
{
    if (reader == NULL || reader->stream == NULL ||
        reader->buffer == NULL || reader->capacity == 0 ||
        character == NULL) {
        return -1;
    }

    if (reader->position >= reader->length) {
        reader->length = fread(reader->buffer, 1, reader->capacity,
                               reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            return ferror(reader->stream) ? -1 : 0;
        }
    }

    *character = reader->buffer[reader->position++];
    return 1;
}

static int read_token(InputReader *reader, char **output,
                      size_t *output_length)
{
    const size_t maximum_capacity = MAX_TOKEN_LENGTH + 1;
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    unsigned char character;
    int status;

    if (reader == NULL || output == NULL || output_length == NULL) {
        return -1;
    }

    *output = NULL;
    *output_length = 0;

    do {
        status = read_character(reader, &character);
        if (status <= 0) {
            return status;
        }
    } while (isspace((unsigned char)character));

    if (capacity > maximum_capacity) {
        capacity = maximum_capacity;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        if (length >= MAX_TOKEN_LENGTH) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity >= maximum_capacity) {
                free(buffer);
                return -1;
            }

            if (capacity > maximum_capacity / 2) {
                new_capacity = maximum_capacity;
            } else {
                new_capacity = capacity * 2;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;

        status = read_character(reader, &character);
        if (status < 0) {
            free(buffer);
            return -1;
        }

        if (status == 0 || isspace((unsigned char)character)) {
            break;
        }
    }

    buffer[length] = '\0';
    *output = buffer;
    *output_length = length;

    return 1;
}

static int minimum_swaps(const char *source, size_t source_length,
                         const char *target, size_t target_length,
                         size_t *result)
{
    size_t index;
    size_t zero_to_one = 0;
    size_t one_to_zero = 0;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    for (index = 0; index < source_length; ++index) {
        if (source[index] != '0' && source[index] != '1') {
            return -1;
        }
    }

    for (index = 0; index < target_length; ++index) {
        if (target[index] != '0' && target[index] != '1') {
            return -1;
        }
    }

    if (source_length != target_length) {
        return 1;
    }

    for (index = 0; index < source_length; ++index) {
        if (source[index] == '0' && target[index] == '1') {
            ++zero_to_one;
        } else if (source[index] == '1' && target[index] == '0') {
            ++one_to_zero;
        }
    }

    if (zero_to_one != one_to_zero) {
        return 1;
    }

    *result = zero_to_one;
    return 0;
}

int main(void)
{
    InputReader reader = { 0 };
    char *source = NULL;
    char *target = NULL;
    size_t source_length = 0;
    size_t target_length = 0;
    size_t swaps = 0;
    int status;

    if (input_reader_init(&reader, stdin) != 0) {
        fprintf(stderr, "Failed to initialize input reader.\n");
        return EXIT_FAILURE;
    }

    status = read_token(&reader, &source, &source_length);
    if (status != 1) {
        fprintf(stderr, "Failed to read the first binary string.\n");
        input_reader_destroy(&reader);
        return EXIT_FAILURE;
    }

    status = read_token(&reader, &target, &target_length);
    if (status != 1) {
        fprintf(stderr, "Failed to read the second binary string.\n");
        free(source);
        input_reader_destroy(&reader);
        return EXIT_FAILURE;
    }

    status = minimum_swaps(source, source_length, target, target_length,
                           &swaps);

    free(source);
    free(target);
    input_reader_destroy(&reader);

    if (status < 0) {
        fprintf(stderr, "Invalid binary string.\n");
        return EXIT_FAILURE;
    }

    if (status > 0) {
        puts("-1");
        return EXIT_SUCCESS;
    }

    printf("%zu\n", swaps);
    return EXIT_SUCCESS;
}