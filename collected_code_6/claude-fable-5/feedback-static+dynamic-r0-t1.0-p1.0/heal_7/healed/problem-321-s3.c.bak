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
    size_t bufsize;
    char *result;
    int written;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    if (len == 0) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (str[i] != '1') {
            return NULL;
        }
    }

    bufsize = 1;
    for (i = 1; i <= len; i++) {
        bufsize += count_digits(i);
        if (i < len) {
            bufsize += count_digits(i);
        }
    }

    result = malloc(bufsize);
    if (result == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 1; i <= len; i++) {
        written = sprintf(result + pos, "%zu", i);
        if (written < 0) {
            free(result);
            return NULL;
        }
        pos += (size_t)written;
    }

    for (i = len - 1; i >= 1; i--) {
        written = sprintf(result + pos, "%zu", i);
        if (written < 0) {
            free(result);
            return NULL;
        }
        pos += (size_t)written;
        if (i == 1) {
            break;
        }
    }

    result[pos] = '\0';

    return result;
}

int main(void)
{
    char input[64];
    char *demlo;

    printf("Enter a repunit number (only 1s): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\r\n")] = '\0';

    demlo = find_demlo(input);
    if (demlo == NULL) {
        fprintf(stderr, "Invalid input: must be a repunit of one or more 1s\n");
        return EXIT_FAILURE;
    }

    printf("Demlo number: %s\n", demlo);
    free(demlo);

    return EXIT_SUCCESS;
}