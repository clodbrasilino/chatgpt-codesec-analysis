#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t count_digits(size_t n)
{
    size_t d = 1;

    while (n >= 10) {
        n /= 10;
        d++;
    }
    return d;
}

char *find_demlo(const char *str)
{
    size_t len;
    size_t i;
    size_t pos;
    size_t total;
    char *result;
    int written;

    if (str == NULL) {
        return NULL;
    }

    len = strnlen(str, 128);
    if (len == 0) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (str[i] != '1') {
            return NULL;
        }
    }

    total = 0;
    for (i = 1; i <= len; i++) {
        total += 2 * count_digits(i);
    }
    total -= count_digits(len);

    result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 1; i <= len; i++) {
        written = snprintf(result + pos, total + 1 - pos, "%zu", i);
        if (written < 0 || (size_t)written >= total + 1 - pos) {
            free(result);
            return NULL;
        }
        pos += (size_t)written;
    }

    for (i = len; i-- > 1;) {
        written = snprintf(result + pos, total + 1 - pos, "%zu", i);
        if (written < 0 || (size_t)written > total - pos) {
            free(result);
            return NULL;
        }
        pos += (size_t)written;
    }
    result[pos] = '\0';

    return result;
}

int main(void)
{
    char input[128];
    char *demlo;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    demlo = find_demlo(input);
    if (demlo == NULL) {
        fprintf(stderr, "Invalid input: must be a repunit of ones\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", demlo);
    free(demlo);

    return EXIT_SUCCESS;
}