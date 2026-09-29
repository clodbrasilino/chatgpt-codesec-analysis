#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

int first_repeated_char(const char *str)
{
    bool seen[256] = { false };
    size_t i;

    if (str == NULL) {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return (int)c;
        }
        seen[c] = true;
    }

    return -1;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    int result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    result = first_repeated_char(buffer);

    if (result == -1) {
        printf("No repeated character found\n");
    } else {
        printf("First repeated character: %c\n", (char)result);
    }

    return EXIT_SUCCESS;
}