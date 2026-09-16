#include <stdio.h>
#include <stdbool.h>

int first_repeated_char(const char *str)
{
    bool seen[256] = { false };
    size_t i;

    if (str == NULL) {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return (int)c;
        }
        seen[c] = true;
    }

    return -1;
}

int main(void)
{
    char buffer[256];
    int result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    result = first_repeated_char(buffer);

    if (result == -1 || result == (int)'\n') {
        printf("No repeated character found\n");
    } else {
        printf("First repeated character: %c\n", (char)result);
    }

    return 0;
}