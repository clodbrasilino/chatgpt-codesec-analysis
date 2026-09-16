#include <stdio.h>
#include <stdlib.h>
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
        return -1;
    }

    len = strlen(str);
    if (len < 2U) {
        return 0;
    }

    for (i = 0U; i < len; i++) {
        int has_vowel_neighbor = 0;

        if (i > 0U && is_vowel(str[i - 1U])) {
            has_vowel_neighbor = 1;
        }
        if (i < (len - 1U) && is_vowel(str[i + 1U])) {
            has_vowel_neighbor = 1;
        }
        if (has_vowel_neighbor) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    const char *test1 = "bestinstareels";
    const char *test2 = "partofthejourneyistheend";
    const char *test3 = "amazonprime";
    int result;

    result = count_chars_with_vowel_neighbors(test1);
    if (result < 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Count for \"%s\": %d\n", test1, result);

    result = count_chars_with_vowel_neighbors(test2);
    if (result < 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Count for \"%s\": %d\n", test2, result);

    result = count_chars_with_vowel_neighbors(test3);
    if (result < 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Count for \"%s\": %d\n", test3, result);

    return EXIT_SUCCESS;
}