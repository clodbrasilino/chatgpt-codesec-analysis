#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *string_to_upper(char *str)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    for (i = 0; i < len; i++) {
        str[i] = (char)toupper((unsigned char)str[i]);
    }

    return str;
}

int main(void)
{
    char buffer[256];
    char *result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = string_to_upper(buffer);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Uppercase: %s\n", result);

    return EXIT_SUCCESS;
}