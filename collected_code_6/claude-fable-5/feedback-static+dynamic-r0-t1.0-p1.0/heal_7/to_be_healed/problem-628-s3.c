#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'My%20Name%20is%20Dawood', got <no output>
  *  test case 1 failed: expected 'I%20am%20a%20Programmer', got <no output>
  *  test case 2 failed: expected 'I%20love%20Coding', got <no output>
  */

char *replace_spaces(const char *input)
{
    size_t len;
    size_t space_count;
    size_t new_len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    space_count = 0;
    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            space_count++;
        }
    }

    if (space_count > (SIZE_MAX - len - 1) / 2) {
        return NULL;
    }

    new_len = len + (space_count * 2);

    result = malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
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

static char *read_input_line(void)
{
    char *buffer;
    size_t len;

    buffer = malloc(MAX_INPUT_LEN);
    if (buffer == NULL) {
        return NULL;
    }

    if (fgets(buffer, MAX_INPUT_LEN, stdin) == NULL) {
        free(buffer);
        return NULL;
    }

    buffer[MAX_INPUT_LEN - 1] = '\0';
    len = strnlen(buffer, MAX_INPUT_LEN);
    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[len - 1] = '\0';
        len--;
    }

    return buffer;
}

static char *join_args(int argc, char *const argv[])
{
    size_t total;
    size_t offset;
    int i;
    char *buffer;

    total = 0;
    for (i = 1; i < argc; i++) {
        size_t len;

        if (argv[i] == NULL) {
            return NULL;
        }

        len = strnlen(argv[i], MAX_INPUT_LEN);
        if (len >= MAX_INPUT_LEN) {
            return NULL;
        }
        if (len > MAX_INPUT_LEN - 1 - total) {
            return NULL;
        }
        total += len;
        if (i < argc - 1) {
            if (total >= MAX_INPUT_LEN - 1) {
                return NULL;
            }
            total++;
        }
    }

    buffer = malloc(total + 1);
    if (buffer == NULL) {
        return NULL;
    }

    offset = 0;
    for (i = 1; i < argc; i++) {
        size_t len;

        len = strnlen(argv[i], MAX_INPUT_LEN);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer + offset, argv[i], len);
        offset += len;
        if (i < argc - 1) {
            buffer[offset] = ' ';
            offset++;
        }
    }
    buffer[offset] = '\0';

    return buffer;
}

int main(int argc, char *argv[])
{
    char *line;
    char *converted;

    line = NULL;

    if (argc > 1) {
        line = join_args(argc, argv);
        if (line == NULL) {
            fprintf(stderr, "Failed to process arguments\n");
            return EXIT_FAILURE;
        }
    } else {
        line = read_input_line();
        if (line == NULL) {
            fprintf(stderr, "Failed to read input\n");
            return EXIT_FAILURE;
        }
    }

    converted = replace_spaces(line);
    if (converted == NULL) {
        fprintf(stderr, "Failed to replace spaces\n");
        free(line);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", converted) < 0) {
        free(converted);
        free(line);
        return EXIT_FAILURE;
    }

    fflush(stdout);

    free(converted);
    converted = NULL;
    free(line);
    line = NULL;

    return EXIT_SUCCESS;
}