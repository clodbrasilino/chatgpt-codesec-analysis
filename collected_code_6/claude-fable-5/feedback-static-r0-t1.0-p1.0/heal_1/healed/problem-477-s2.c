#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

void string_to_lower(char *str)
{
    size_t i;

    if (str == NULL) {
        return;
    }

    for (i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int main(void)
{
    char *buffer;

    buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter a string: ");

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    string_to_lower(buffer);

    printf("Lowercase: %s\n", buffer);

    free(buffer);

    return 0;
}