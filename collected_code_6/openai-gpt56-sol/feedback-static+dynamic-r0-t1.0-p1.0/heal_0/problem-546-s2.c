#include <stdio.h>
#include <string.h>

const char *find_last_char(const char *string, int character)
{
    if (string == NULL) {
        return NULL;
    }

    return strrchr(string, character);
}

int main(void)
{
    const char string[] = "The quick brown fox jumps over the lazy dog";
    const int character = 'o';
    const char *result = find_last_char(string, character);

    if (result == NULL) {
        printf("Character '%c' not found.\n", character);
        return 0;
    }

    printf("Last occurrence of '%c' is at index %zu.\n",
           character, (size_t)(result - string));

    return 0;
}