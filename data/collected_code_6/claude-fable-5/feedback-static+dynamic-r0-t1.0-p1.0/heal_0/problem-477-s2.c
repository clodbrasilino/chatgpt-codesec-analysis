#include <stdio.h>
#include <string.h>
#include <ctype.h>

void string_to_lower(char *str)
{
    size_t i;

    if (str == NULL) {
        return;
    }

    for (i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int main(void)
{
    char buffer[256];

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    string_to_lower(buffer);

    printf("Lowercase: %s\n", buffer);

    return 0;
}