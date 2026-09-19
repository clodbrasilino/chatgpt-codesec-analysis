#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int is_word_separator(unsigned char character)
{
    return character == ' ' ||
           character == '\t' ||
           character == '\r' ||
           character == '\n' ||
           character == '\v' ||
           character == '\f';
}

static int word_is_seen(char *const *seen, size_t count, const char *word)
{
    size_t index;

    for (index = 0; index < count; ++index) {
        if (strcmp(seen[index], word) == 0) {
            return 1;
        }
    }

    return 0;
}

static int add_seen_word(char ***seen, size_t *count, size_t *capacity,
                         char *word)
{
    if (*count == *capacity) {
        size_t new_capacity;
        char **new_seen;

        if (*capacity == 0) {
            new_capacity = 8;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }

            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*new_seen)) {
            return 0;
        }

        new_seen = realloc(*seen, new_capacity * sizeof(*new_seen));
        if (new_seen == NULL) {
            return 0;
        }

        *seen = new_seen;
        *capacity = new_capacity;
    }

    (*seen)[*count] = word;
    ++(*count);

    return 1;
}

char *remove_duplicate_words(const char *input)
{
    char *copy;
    char *output;
    char **seen;
    char *cursor;
    size_t input_length;
    size_t output_length;
    size_t seen_count;
    size_t seen_capacity;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);

    if (input_length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(input_length + 1);
    if (copy == NULL) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        free(copy);
        return NULL;
    }

    memcpy(copy, input, input_length + 1);

    seen = NULL;
    seen_count = 0;
    seen_capacity = 0;
    output_length = 0;
    cursor = copy;

    while (*cursor != '\0') {
        char *word;
        char *word_end;
        size_t word_length;

        while (*cursor != '\0' &&
               is_word_separator((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            break;
        }

        word = cursor;

        while (*cursor != '\0' &&
               !is_word_separator((unsigned char)*cursor)) {
            ++cursor;
        }

        word_end = cursor;
        word_length = (size_t)(word_end - word);

        if (*cursor != '\0') {
            *cursor = '\0';
            ++cursor;
        }

        if (word_is_seen(seen, seen_count, word)) {
            continue;
        }

        if (!add_seen_word(&seen, &seen_count, &seen_capacity, word)) {
            free(seen);
            free(output);
            free(copy);
            return NULL;
        }

        if (output_length != 0) {
            output[output_length++] = ' ';
        }

        memcpy(output + output_length, word, word_length);
        output_length += word_length;
    }

    output[output_length] = '\0';

    free(seen);
    free(copy);

    return output;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *input;
    char *result;
    char *position;
    size_t total_length;
    int index;
    int status;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    total_length = 0;

    for (index = 1; index < argc; ++index) {
        size_t argument_length = strlen(argv[index]);

        if (index > 1) {
            if (total_length == SIZE_MAX) {
                fprintf(stderr, "Input is too large\n");
                return EXIT_FAILURE;
            }

            ++total_length;
        }

        if (argument_length > SIZE_MAX - total_length) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        total_length += argument_length;
    }

    if (total_length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    input = malloc(total_length + 1);
    if (input == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    position = input;

    for (index = 1; index < argc; ++index) {
        size_t argument_length = strlen(argv[index]);

        if (index > 1) {
            *position++ = ' ';
        }

        memcpy(position, argv[index], argument_length);
        position += argument_length;
    }

    *position = '\0';

    result = remove_duplicate_words(input);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Failed to process the input string\n");
        return EXIT_FAILURE;
    }

    status = EXIT_SUCCESS;

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free(result);

    return status;
}