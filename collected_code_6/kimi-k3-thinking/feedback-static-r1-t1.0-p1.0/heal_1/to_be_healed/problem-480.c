#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHARS 256
#define INPUT_SIZE 1024

int find_max_occurring_char(const char *str, char *max_char, size_t *max_count)
{
    size_t counts[NUM_CHARS] = {0};
    size_t highest = 0;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    unsigned char c;

    if (str == NULL || max_char == NULL || max_count == NULL) {
        return -1;
    }

    if (str[0] == '\0') {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > highest) {
            highest = counts[c];
            *max_char = (char)c;
        }
    }

    *max_count = highest;
    return 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    char max_char = '\0';
    size_t max_count = 0;

    printf("Enter a string: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (find_max_occurring_char(input, &max_char, &max_count) != 0) {
        fprintf(stderr, "Error: invalid or empty string.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum occurring character: '%c'\n", max_char);
    printf("Occurrences: %zu\n", max_count);

    return EXIT_SUCCESS;
}