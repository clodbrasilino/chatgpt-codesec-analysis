#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_multiple_spaces(const char *input)
{
    if (input == NULL)
        return NULL;

    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL)
        return NULL;

    size_t i = 0, j = 0;
    int space_pending = 0;

    while (i < len && isspace((unsigned char)input[i]))
        i++;

    for (; i < len; i++) {
        if (isspace((unsigned char)input[i])) {
            space_pending = 1;
        } else {
            if (space_pending && j > 0)
                result[j++] = ' ';
            result[j++] = input[i];
            space_pending = 0;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char input[1024];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = '\0';

    char *cleaned = remove_multiple_spaces(input);
    if (cleaned == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", cleaned);
    free(cleaned);

    return EXIT_SUCCESS;
}