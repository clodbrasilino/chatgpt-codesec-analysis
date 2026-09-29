#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char add_all_characters(const char *str)
{
    int sum = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return '\0';
    }

    len = strlen(str);
    for (i = 0; i < len; i++) {
        sum += (unsigned char)str[i];
    }

    return (char)(sum % 256);
}

int main(void)
{
    char buffer[256];
    char result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = add_all_characters(buffer);
    printf("Resulting character: %c (ASCII: %d)\n", 
           (result >= 32 && result <= 126) ? result : '.', 
           (unsigned char)result);

    return EXIT_SUCCESS;
}