#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT 256
#define MAX_MATCHES 64

typedef struct {
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
        if ((i + 1 < len) &&
            isupper((unsigned char)input[i]) &&
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

            if (match_len > 0 && match_len <= len - start) {
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