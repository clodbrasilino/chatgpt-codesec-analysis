#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int add_spaces_before_capitals(const char *input, char **output)
{
    static const char pattern[] = "([a-z0-9])([A-Z])";
    regex_t regex;
    regmatch_t matches[3];
    size_t input_len;
    size_t capacity;
    size_t read_pos = 0;
    size_t write_pos = 0;
    char *result;
    int rc;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    input_len = strlen(input);

    if (input_len > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    capacity = input_len * 2U + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    rc = regcomp(&regex, pattern, REG_EXTENDED);
    if (rc != 0) {
        free(result);
        return -1;
    }

    while (read_pos < input_len) {
        rc = regexec(&regex, input + read_pos, 3, matches, 0);

        if (rc == REG_NOMATCH) {
            size_t remaining = input_len - read_pos;

            memcpy(result + write_pos, input + read_pos, remaining);
            write_pos += remaining;
            break;
        }

        if (rc != 0 ||
            matches[0].rm_so < 0 ||
            matches[0].rm_eo < 0 ||
            matches[1].rm_so < 0 ||
            matches[1].rm_eo < 0 ||
            matches[2].rm_so < 0 ||
            matches[2].rm_eo < 0) {
            regfree(&regex);
            free(result);
            return -1;
        }

        {
            size_t second_group = read_pos + (size_t)matches[2].rm_so;
            size_t prefix_len;

            if (second_group < read_pos || second_group >= input_len) {
                regfree(&regex);
                free(result);
                return -1;
            }

            prefix_len = second_group - read_pos;

            if (prefix_len > capacity - write_pos - 1U) {
                regfree(&regex);
                free(result);
                return -1;
            }

            memcpy(result + write_pos, input + read_pos, prefix_len);
            write_pos += prefix_len;
            result[write_pos++] = ' ';
            read_pos = second_group;
        }
    }

    result[write_pos] = '\0';
    regfree(&regex);
    *output = result;
    return 0;
}

int main(void)
{
    char input[4096];
    char *output = NULL;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    {
        size_t length = strlen(input);

        if (length > 0U && input[length - 1U] == '\n') {
            input[length - 1U] = '\0';
        } else if (!feof(stdin)) {
            int ch;

            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            return EXIT_FAILURE;
        }
    }

    if (add_spaces_before_capitals(input, &output) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}