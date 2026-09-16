#include <errno.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *insert_spaces_before_capitals(const char *input)
{
    const char *pattern = "([[:lower:][:digit:]])([[:upper:]])";
    regex_t regex;
    regmatch_t matches[3];
    size_t input_length;
    size_t input_position = 0;
    size_t output_position = 0;
    size_t capacity;
    char *output;
    int status;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    input_length = strlen(input);

    if (input_length > (SIZE_MAX - 1U) / 2U) {
        errno = EOVERFLOW;
        return NULL;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        errno = EINVAL;
        return NULL;
    }

    capacity = (input_length * 2U) + 1U;
    output = malloc(capacity);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (input_position < input_length) {
        size_t split_offset;
        size_t remaining_length = input_length - input_position;

        status = regexec(&regex, input + input_position, 3, matches, 0);
        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0 || matches[2].rm_so <= 0) {
            free(output);
            regfree(&regex);
            errno = EIO;
            return NULL;
        }

        split_offset = (size_t)matches[2].rm_so;

        if (split_offset > remaining_length ||
            split_offset > capacity - output_position ||
            capacity - output_position - split_offset < 2U) {
            free(output);
            regfree(&regex);
            errno = EOVERFLOW;
            return NULL;
        }

        memcpy(output + output_position,
               input + input_position,
               split_offset);

        output_position += split_offset;
        output[output_position++] = ' ';
        input_position += split_offset;
    }

    {
        size_t remaining_length = input_length - input_position;

        if (remaining_length > capacity - output_position ||
            capacity - output_position - remaining_length < 1U) {
            free(output);
            regfree(&regex);
            errno = EOVERFLOW;
            return NULL;
        }

        memcpy(output + output_position,
               input + input_position,
               remaining_length);

        output_position += remaining_length;
    }

    output[output_position] = '\0';
    regfree(&regex);

    return output;
}

int main(int argc, char *argv[const])
{
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = insert_spaces_before_capitals(argv[1]);
    if (result == NULL) {
        perror("Unable to transform string");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}