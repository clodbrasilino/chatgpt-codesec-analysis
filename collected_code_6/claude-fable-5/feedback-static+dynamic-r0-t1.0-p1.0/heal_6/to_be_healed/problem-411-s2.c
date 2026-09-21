#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

static size_t bounded_length(const char *str, size_t max_len)
{
    size_t len = 0U;

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    return len;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  */

static char *snake_to_camel(const char *input)
{
    char *result;
    size_t len;
    size_t in_pos;
    size_t out_pos;
    int capitalize_next;

    if (input == NULL) {
        return NULL;
    }

    len = bounded_length(input, MAX_INPUT_LEN);

    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    out_pos = 0U;
    capitalize_next = 1;

    for (in_pos = 0U; in_pos < len; in_pos++) {
        unsigned char c = (unsigned char)input[in_pos];

        if (c == (unsigned char)'_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next != 0) {
                result[out_pos] = (char)toupper((int)c);
                capitalize_next = 0;
            } else {
                result[out_pos] = (char)c;
            }
            out_pos++;
        }
    }

    result[out_pos] = '\0';

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[MAX_INPUT_LEN + 2U];
    int status = EXIT_SUCCESS;

    while (fgets(line, (int)sizeof(line), stdin) != NULL) {
        size_t len;
        char *converted;

        line[sizeof(line) - 1U] = '\0';
        len = bounded_length(line, sizeof(line) - 1U);

        while (len > 0U && (line[len - 1U] == '\n' || line[len - 1U] == '\r')) {
            line[len - 1U] = '\0';
            len--;
        }

        if (len == 0U) {
            continue;
        }

        converted = snake_to_camel(line);
        if (converted == NULL) {
            (void)fprintf(stderr, "Conversion failed for: %s\n", line);
            status = EXIT_FAILURE;
            continue;
        }

        if (printf("%s\n", converted) < 0) {
            free(converted);
            status = EXIT_FAILURE;
            break;
        }

        free(converted);

        if (fflush(stdout) != 0) {
            status = EXIT_FAILURE;
            break;
        }
    }

    return status;
}