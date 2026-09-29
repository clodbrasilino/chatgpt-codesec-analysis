#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024

size_t count_vowels(const char *str)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        int c = tolower((unsigned char)str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }

    return count;
}

int main(void)
{
    char buffer[MAX_INPUT];
    size_t len;
    size_t vowels;

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    vowels = count_vowels(buffer);
    printf("Number of vowels: %zu\n", vowels);

    return EXIT_SUCCESS;
}