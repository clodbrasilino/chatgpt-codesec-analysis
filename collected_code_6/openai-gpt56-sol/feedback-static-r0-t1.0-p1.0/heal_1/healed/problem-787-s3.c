#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matches(const char *string)
{
    return string != NULL && strcmp(string, "abbb") == 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);
        return 1;
    }

    input[strcspn(input, "\r\n")] = '\0';

    puts(matches(input) ? "Match" : "No match");

    free(input);
    return 0;
}