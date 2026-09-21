#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEXT_LEN 4096

int find_sequences(const char *text, size_t max_len, void (*callback)(const char *, size_t))
{
    size_t i;
    size_t len;
    int count;

    if (text == NULL || callback == NULL) {
        return -1;
    }

    len = 0;
    while (len < max_len && text[len] != '\0') {
        len++;
    }

    if (len == max_len) {
        return -1;
    }

    count = 0;
    i = 0;

    while (i < len) {
        if (isupper((unsigned char)text[i]) &&
            (i + 1 < len) &&
            islower((unsigned char)text[i + 1])) {
            size_t start = i;
            size_t j = i + 1;

            while (j < len && islower((unsigned char)text[j])) {
                j++;
            }

            callback(&text[start], j - start);
            count++;
            i = j;
        } else {
            i++;
        }
    }

    return count;
}

static void print_match(const char *start, size_t length)
{
    if (start == NULL || length == 0) {
        return;
    }

    if (fwrite(start, sizeof(char), length, stdout) != length) {
        return;
    }

    if (putchar('\n') == EOF) {
        return;
    }
}

int main(void)
{
    const char *test_strings[] = {
        "Hello World FooBar xyzAbc",
        "NOMATCHhere Ab X y Zz",
        "",
        "PlainText With Mixed CASES and Words"
    };
    size_t num_tests;
    size_t i;

    num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (i = 0; i < num_tests; i++) {
        int result;

        if (printf("Input: \"%s\"\n", test_strings[i]) < 0) {
            return EXIT_FAILURE;
        }

        result = find_sequences(test_strings[i], MAX_TEXT_LEN, print_match);

        if (result < 0) {
            if (fprintf(stderr, "Error processing string\n") < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }

        if (printf("Matches found: %d\n\n", result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}