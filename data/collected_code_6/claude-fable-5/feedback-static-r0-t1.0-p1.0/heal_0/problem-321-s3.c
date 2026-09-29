#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_demlo(const char *str)
{
    size_t len;
    size_t i;
    size_t pos;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    if (len == 0 || len > 9) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (str[i] != '1') {
            return NULL;
        }
    }

    result = malloc((2 * len - 1) + 1);
    if (result == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 1; i <= len; i++) {
        result[pos++] = (char)('0' + i);
    }
    for (i = len - 1; i >= 1; i--) {
        result[pos++] = (char)('0' + i);
    }
    result[pos] = '\0';

    return result;
}

int main(void)
{
    char input[32];
    char *demlo;

    printf("Enter a repunit number (only 1s, max 9 digits): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    demlo = find_demlo(input);
    if (demlo == NULL) {
        fprintf(stderr, "Invalid input: must be a repunit of 1 to 9 ones\n");
        return EXIT_FAILURE;
    }

    printf("Demlo number: %s\n", demlo);
    free(demlo);

    return EXIT_SUCCESS;
}