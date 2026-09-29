#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

size_t count_lowercase(const char *str)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (islower((unsigned char)str[i])) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    char buffer[256];
    size_t result;
    size_t len;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = count_lowercase(buffer);

    printf("Number of lowercase letters: %zu\n", result);

    return EXIT_SUCCESS;
}