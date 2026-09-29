#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

char *remove_lowercase(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if (!islower((unsigned char)input[i])) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    while ((nread = getline(&buffer, &bufsize, stdin)) != -1) {
        if (nread > 0 && buffer[nread - 1] == '\n') {
            buffer[nread - 1] = '\0';
        }

        char *output = remove_lowercase(buffer);
        if (output == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free(buffer);
            return EXIT_FAILURE;
        }

        printf("%s\n", output);
        fflush(stdout);
        free(output);
    }

    free(buffer);

    return EXIT_SUCCESS;
}