#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t n = 0;

    while (n < max_len && s[n] != '\0') {
        n++;
    }
    return n;
}

static int safe_copy(char *dest, size_t dest_size, const char *src, size_t src_len)
{
    size_t i;

    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (src_len >= dest_size) {
        return -1;
    }
    for (i = 0; i < src_len; i++) {
        dest[i] = src[i];
    }
    dest[src_len] = '\0';
    return 0;
}

static int build_input_from_args(char *dest, size_t dest_size, int argc, char const *argv[])
{
    size_t pos = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'arg_len' can be reduced. [variableScope]
     */
    size_t arg_len;
    int i;

    if (dest == NULL || argv == NULL) {
        return -1;
    }

    for (i = 1; i < argc; i++) {
        arg_len = bounded_strlen(argv[i], MAX_INPUT_LEN);
        if (arg_len >= MAX_INPUT_LEN) {
            return -1;
        }
        if (i > 1) {
            if (pos + 1 >= dest_size) {
                return -1;
            }
            dest[pos] = ' ';
            pos++;
        }
        if (pos + arg_len >= dest_size) {
            return -1;
        }
        if (safe_copy(dest + pos, dest_size - pos, argv[i], arg_len) != 0) {
            return -1;
        }
        pos += arg_len;
    }
    dest[pos] = '\0';
    return 0;
}

char *replace_spaces(const char *input)
{
    size_t len;
    size_t space_count = 0;
    size_t i;
    size_t j = 0;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = bounded_strlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            space_count++;
        }
    }

    if (space_count > (SIZE_MAX - len - 1) / 2) {
        return NULL;
    }

    result = malloc(len + (space_count * 2) + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            result[j] = '%';
            result[j + 1] = '2';
            result[j + 2] = '0';
            j += 3;
        } else {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(int argc, char const *argv[])
{
    char *input;
    char *converted;
    size_t len;

    input = calloc(MAX_INPUT_LEN, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    if (argc > 1) {
        if (build_input_from_args(input, MAX_INPUT_LEN, argc, argv) != 0) {
            fprintf(stderr, "Input too long\n");
            free(input);
            return EXIT_FAILURE;
        }
    } else {
        if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
            fprintf(stderr, "Failed to read input\n");
            free(input);
            return EXIT_FAILURE;
        }
        input[MAX_INPUT_LEN - 1] = '\0';
    }

    len = bounded_strlen(input, MAX_INPUT_LEN);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    converted = replace_spaces(input);
    if (converted == NULL) {
        fprintf(stderr, "Failed to process string\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", converted) < 0) {
        free(converted);
        free(input);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        free(converted);
        free(input);
        return EXIT_FAILURE;
    }

    free(converted);
    converted = NULL;
    free(input);
    input = NULL;

    return EXIT_SUCCESS;
}