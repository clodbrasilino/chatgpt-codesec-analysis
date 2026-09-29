#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096U

static size_t bounded_strlen(const char *s, size_t maxlen)
{
    size_t n = 0U;
    while ((n < maxlen) && (s[n] != '\0')) {
        n++;
    }
    return n;
}

static char *camel_to_snake(const char *input)
{
    size_t len;
    size_t out_size;
    size_t i;
    size_t j;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    len = bounded_strlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    if (len > ((SIZE_MAX - 1U) / 2U)) {
        return NULL;
    }
    out_size = (len * 2U) + 1U;

    output = (char *)malloc(out_size);
    if (output == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (isupper((int)c) != 0) {
            if (i > 0U) {
                output[j] = '_';
                j++;
            }
            output[j] = (char)tolower((int)c);
            j++;
        } else {
            output[j] = (char)c;
            j++;
        }
    }
    output[j] = '\0';

    return output;
}

static int process_line(const char *line)
{
    char *result;

    result = camel_to_snake(line);
    if (result == NULL) {
        (void)fprintf(stderr, "Conversion failed for input\n");
        return -1;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return -1;
    }

    if (fflush(stdout) != 0) {
        free(result);
        return -1;
    }

    free(result);
    return 0;
}

int main(int argc, const char *const argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];

    if (argc > 1) {
        int i;
        for (i = 1; i < argc; i++) {
            if (process_line(argv[i]) != 0) {
                return EXIT_FAILURE;
            }
        }
        return EXIT_SUCCESS;
    }

    (void)memset(buffer, 0, sizeof(buffer));

    while (fgets(buffer, (int)sizeof(buffer), stdin) != NULL) {
        size_t blen = bounded_strlen(buffer, sizeof(buffer));

        while ((blen > 0U) &&
               ((buffer[blen - 1U] == '\n') || (buffer[blen - 1U] == '\r'))) {
            buffer[blen - 1U] = '\0';
            blen--;
        }

        if (process_line(buffer) != 0) {
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}