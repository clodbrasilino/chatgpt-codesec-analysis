#include <stdio.h>
#include <string.h>

char find_first_repeated(const char *str)
{
    if (str == NULL || str[0] == '\0')
        return '\0';

    int seen[256] = {0};
    size_t i;

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c])
            return str[i];
        seen[c] = 1;
    }

    return '\0';
}

int main(void)
{
    char input[1024];
    char result;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    result = find_first_repeated(input);

    if (result != '\0')
        printf("First repeated character: %c\n", result);
    else
        printf("No repeated character found\n");

    return 0;
}