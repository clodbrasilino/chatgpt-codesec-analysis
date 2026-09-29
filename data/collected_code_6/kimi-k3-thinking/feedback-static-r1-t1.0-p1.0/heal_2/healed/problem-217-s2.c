#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOOKUP_SIZE 256
#define BUFFER_SIZE 1024

char find_first_repeated(const char *str)
{
    unsigned char seen[LOOKUP_SIZE] = {0};
    size_t i;

    if (str == NULL) {
        return '\0';
    }

    for (i = 0; str[i] != '\0' && i < BUFFER_SIZE; i++) {
        size_t index = (size_t)(unsigned char)str[i];
        if (index >= sizeof(seen)) {
            continue;
        }
        if (seen[index]) {
            return (char)index;
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

    len = strcspn(buffer, "\n");
    if (len < sizeof(buffer) && buffer[len] == '\n') {
        buffer[len] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    result = find_first_repeated(buffer);

    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}