#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool matches(const char *str)
{
    return str != NULL && strcmp(str, "abbb") == 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return status;
    }

    input[strcspn(input, "\r\n")] = '\0';
    puts(matches(input) ? "Match" : "No match");

    free(input);
    return EXIT_SUCCESS;
}