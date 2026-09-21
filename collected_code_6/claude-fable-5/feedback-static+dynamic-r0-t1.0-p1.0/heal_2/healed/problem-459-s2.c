#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

char *remove_uppercase(const char *input);

char *remove_uppercase(const char *input)
{
    char *result;
    size_t input_len;
    size_t result_len;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    result_len = 0;
    for (i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (!isupper(c)) {
            if (result_len >= input_len) {
                free(result);
                return NULL;
            }
            result[result_len] = (char)c;
            result_len++;
        }
    }

    result[result_len] = '\0';
    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "helloWORLDthisIS a TEST string",
        "ALLUPPERCASE",
        "nolowercasehere",
        "MixedCASEString"
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *cleaned = remove_uppercase(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Failed to process string: %s\n", test_strings[i]);
            return EXIT_FAILURE;
        }
        if (printf("Original: \"%s\" -> Result: \"%s\"\n", test_strings[i], cleaned) < 0) {
            free(cleaned);
            return EXIT_FAILURE;
        }
        free(cleaned);
    }

    return EXIT_SUCCESS;
}