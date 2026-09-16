#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_demlo(const char *str)
{
    size_t len;
    size_t i;
    size_t pos;
    size_t bufsize;
    char *result;

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

    bufsize = (2 * len - 1) * 21 + 1;
    result = malloc(bufsize);
    if (result == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 1; i <= len; i++) {
        int written = snprintf(result + pos, bufsize - pos, "%zu", i);
        if (written < 0 || (size_t)written >= bufsize - pos) {
            free(result);
            return NULL;
        }
        pos += (size_t)written;
    }
    for (i = len - 1; i >= 1; i--) {
        int written = snprintf(result + pos, bufsize - pos, "%zu", i);
        if (written < 0 || (size_t)written >= bufsize - pos) {
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