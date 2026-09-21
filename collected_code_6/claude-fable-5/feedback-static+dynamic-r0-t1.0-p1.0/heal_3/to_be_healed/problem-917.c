#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT 256
#define MAX_MATCHES 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char text[MAX_INPUT];
} Match;

int find_sequences(const char *input, Match *matches, size_t max_matches, size_t *count)
{
    size_t i;
    size_t len;
    size_t found;

    if (input == NULL || matches == NULL || count == NULL || max_matches == 0) {
        return -1;
    }

    *count = 0;
    found = 0;
    len = strnlen(input, MAX_INPUT);
    i = 0;

    while (i < len && found < max_matches) {
        if (isupper((unsigned char)input[i]) &&
            (i + 1 < len) &&
            islower((unsigned char)input[i + 1])) {
            size_t start = i;
            size_t j = i + 1;
            size_t match_len;
            size_t dest_size;

            while (j < len && islower((unsigned char)input[j])) {
                j++;
            }

            match_len = j - start;
            dest_size = sizeof(matches[found].text);

            if (match_len >= dest_size) {
                match_len = dest_size - 1;
            }

            if (match_len > 0 && start + match_len <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(matches[found].text, &input[start], match_len);
                matches[found].text[match_len] = '\0';
                found++;
            }

            i = j;
        } else {
            i++;
        }
    }

    *count = found;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];
    Match matches[MAX_MATCHES];
    size_t count;
    size_t len;

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (find_sequences(input, matches, MAX_MATCHES, &count) != 0) {
        fprintf(stderr, "Error processing input\n");
        return EXIT_FAILURE;
    }

    if (count == 0) {
        printf("No matches found\n");
    } else {
        printf("Found %zu match(es):\n", count);
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", matches[i].text);
        }
    }

    return EXIT_SUCCESS;
}