#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MATCH_LEN 256
#define MAX_TEXT_LEN 4096

static size_t bounded_strlen(const char *s, size_t maxlen)
{
    size_t n = 0;

    while (n < maxlen && s[n] != '\0') {
        n++;
    }

    return n;
}

static int find_upper_lower_sequences(const char *text)
{
    size_t i;
    size_t len;
    int found;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char match[MAX_MATCH_LEN];

    if (text == NULL) {
        return -1;
    }

    len = bounded_strlen(text, MAX_TEXT_LEN);
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

                if (match_len > 0U && match_len < sizeof(match)) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
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