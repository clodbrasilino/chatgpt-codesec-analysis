#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

char find_first_repeated(const char *str)
{
    bool seen[256] = { false };
    size_t i;

    if (str == NULL) {
        return '\0';
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return str[i];
        }
        seen[c] = true;
    }

    return '\0';
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    result = find_first_repeated(buffer);

    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return 0;
}