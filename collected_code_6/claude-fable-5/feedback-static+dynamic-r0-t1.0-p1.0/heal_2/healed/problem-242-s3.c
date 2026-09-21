#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

size_t count_characters(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[count] != '\0') {
        count++;
    }

    return count;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t length;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    length = count_characters(buffer);

    printf("%zu\n", length);
    fflush(stdout);

    return EXIT_SUCCESS;
}