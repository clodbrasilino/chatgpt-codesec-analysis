#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int find_first_repeated_char(const char *str, char *result);

int find_first_repeated_char(const char *str, char *result)
{
    bool seen[UCHAR_MAX + 1] = { false };
    size_t i;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (i = 0U; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            *result = str[i];
            return 0;
        }
        seen[c] = true;
    }

    return 1;
}

int main(void)
{
    const char *tests[] = { "programming", "abcdef", "hello world", "" };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < num_tests; i++) {
        char repeated = '\0';
        int status = find_first_repeated_char(tests[i], &repeated);

        if (status == 0) {
            if (printf("First repeated character in \"%s\": '%c'\n",
                       tests[i], repeated) < 0) {
                return 1;
            }
        } else if (status == 1) {
            if (printf("No repeated character found in \"%s\"\n",
                       tests[i]) < 0) {
                return 1;
            }
        } else {
            if (fprintf(stderr, "Invalid input provided\n") < 0) {
                return 1;
            }
            return 1;
        }
    }

    return 0;
}