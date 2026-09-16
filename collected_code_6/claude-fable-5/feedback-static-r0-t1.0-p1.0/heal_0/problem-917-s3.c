#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MATCH_LEN 256

static int find_upper_lower_sequences(const char *text)
{
    size_t i;
    size_t len;
    int found;
    char match[MAX_MATCH_LEN];

    if (text == NULL) {
        return -1;
    }

    len = strlen(text);
    found = 0;
    i = 0;

    while (i < len) {
        if (isupper((unsigned char)text[i]) &&
            (i + 1U) < len &&
            islower((unsigned char)text[i + 1U])) {
            size_t start = i;
            size_t j = i + 1U;

            while (j < len && islower((unsigned char)text[j])) {
                j++;
            }

            {
                size_t match_len = j - start;

                if (match_len < MAX_MATCH_LEN) {
                    memcpy(match, &text[start], match_len);
                    match[match_len] = '\0';
                    if (printf("Found: %s\n", match) < 0) {
                        return -1;
                    }
                    found++;
                }
            }
            i = j;
        } else {
            i++;
        }
    }

    return found;
}

int main(void)
{
    const char *samples[] = {
        "Hello World this is a Test of Sequences",
        "ABC noUpper Xy z Qwerty",
        "nothing here",
        "Single"
    };
    size_t count;
    size_t k;

    count = sizeof(samples) / sizeof(samples[0]);

    for (k = 0; k < count; k++) {
        int result;

        if (printf("Input: %s\n", samples[k]) < 0) {
            return EXIT_FAILURE;
        }

        result = find_upper_lower_sequences(samples[k]);

        if (result < 0) {
            if (fprintf(stderr, "Error processing input\n") < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }

        if (result == 0) {
            if (printf("No matches found\n") < 0) {
                return EXIT_FAILURE;
            }
        }

        if (printf("\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}