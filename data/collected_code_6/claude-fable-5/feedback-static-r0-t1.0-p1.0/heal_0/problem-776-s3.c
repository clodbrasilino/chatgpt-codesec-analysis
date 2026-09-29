#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int is_vowel(char c)
{
    char lower = (char)tolower((unsigned char)c);
    return (lower == 'a' || lower == 'e' || lower == 'i' ||
            lower == 'o' || lower == 'u');
}

int count_chars_with_vowel_neighbors(const char *str)
{
    size_t len;
    size_t i;
    int count = 0;

    if (str == NULL) {
        return 0;
    }

    len = strlen(str);
    if (len == 0) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (i > 0 && is_vowel(str[i - 1])) {
            count++;
            continue;
        }
        if (i + 1 < len && is_vowel(str[i + 1])) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    char buffer[256];
    int result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = count_chars_with_vowel_neighbors(buffer);
    printf("Number of characters with vowel neighbors: %d\n", result);

    return 0;
}