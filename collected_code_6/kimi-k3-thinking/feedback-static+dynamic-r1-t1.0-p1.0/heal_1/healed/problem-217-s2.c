#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define LOOKUP_SIZE (UCHAR_MAX + 1)
#define BUFFER_SIZE 1024

char find_first_repeated(const char *str)
{
    unsigned char *seen;
    size_t i;
    char repeated = '\0';

    if (str == NULL) {
        return '\0';
    }

    seen = calloc(LOOKUP_SIZE, sizeof(*seen));
    if (seen == NULL) {
        return '\0';
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];

        if (seen[c]) {
            repeated = (char)c;
            break;
        }

        seen[c] = 1;
    }

    free(seen);
    return repeated;
}

int main(void)
{
    char *buffer;
    char result;

    printf("Enter a string: ");

    buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = find_first_repeated(buffer);

    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    free(buffer);
    return EXIT_SUCCESS;
}