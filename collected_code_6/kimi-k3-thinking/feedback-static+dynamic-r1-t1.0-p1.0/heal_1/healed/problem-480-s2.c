#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_RANGE 256
#define BUFFER_SIZE 1024

char find_max_occurring_char(const char *str)
{
    int counts[ASCII_RANGE] = {0};
    size_t i;
    char max_char;
    int max_count;

    if (str == NULL || str[0] == '\0') {
        return '\0';
    }

    for (i = 0; str[i] != '\0'; i++) {
        counts[(unsigned char)str[i]]++;
    }

    max_char = str[0];
    max_count = counts[(unsigned char)str[0]];

    for (i = 1; str[i] != '\0'; i++) {
        if (counts[(unsigned char)str[i]] > max_count) {
            max_count = counts[(unsigned char)str[i]];
            max_char = str[i];
        }
    }

    return max_char;
}

static void discard_remaining_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char result;
    size_t len;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        discard_remaining_input();
        fprintf(stderr, "Input exceeds maximum allowed length\n");
        return EXIT_FAILURE;
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "Empty string provided\n");
        return EXIT_FAILURE;
    }

    result = find_max_occurring_char(buffer);

    if (result == '\0') {
        fprintf(stderr, "Could not determine maximum occurring character\n");
        return EXIT_FAILURE;
    }

    printf("Maximum occurring character: '%c'\n", result);

    return EXIT_SUCCESS;
}