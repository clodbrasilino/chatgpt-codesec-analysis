#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define LOOKUP_SIZE (UCHAR_MAX + 1)
#define BUFFER_SIZE 1024

char find_first_repeated(const char *str, size_t str_size)
{
    unsigned char seen[LOOKUP_SIZE] = {0};
    size_t i;

    if (str == NULL || str_size == 0) {
        return '\0';
    }

    for (i = 0; i < str_size && str[i] != '\0'; i++) {
        size_t index = (size_t)(unsigned char)str[i];

        if (index >= sizeof(seen)) {
            continue;
        }

        if (seen[index] != 0) {
            return (char)(unsigned char)index;
        }

        seen[index] = 1;
    }

    return '\0';
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t len;
    char result;

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strcspn(buffer, "\n");

    if (buffer[len] == '\n') {
        buffer[len] = '\0';
    } else {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
            ;
        }
    }

    result = find_first_repeated(buffer, sizeof(buffer));

    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}