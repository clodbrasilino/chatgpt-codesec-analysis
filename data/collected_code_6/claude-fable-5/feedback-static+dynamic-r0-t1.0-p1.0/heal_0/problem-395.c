#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_first_non_repeated(const char *str, char *result)
{
    size_t counts[256] = {0};
    size_t i;
    size_t len;

    if (str == NULL || result == NULL) {
        return -1;
    }

    len = strlen(str);

    for (i = 0; i < len; i++) {
        counts[(unsigned char)str[i]]++;
    }

    for (i = 0; i < len; i++) {
        if (counts[(unsigned char)str[i]] == 1) {
            *result = str[i];
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    const char *test_strings[] = {
        "swiss",
        "aabbcc",
        "programming",
        ""
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;
    char result;
    int status;

    for (i = 0; i < num_tests; i++) {
        status = find_first_non_repeated(test_strings[i], &result);
        if (status == 0) {
            if (printf("First non-repeated character in \"%s\": %c\n",
                       test_strings[i], result) < 0) {
                return EXIT_FAILURE;
            }
        } else if (status == 1) {
            if (printf("No non-repeated character found in \"%s\"\n",
                       test_strings[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (fprintf(stderr, "Invalid input provided\n") < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}