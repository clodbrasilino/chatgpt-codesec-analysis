#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t find_literals(
    const char *text,
    const char *const literals[],
    size_t literal_count,
    const char **matched_literal,
    size_t *match_position)
{
    size_t best_position = SIZE_MAX;
    size_t best_index = SIZE_MAX;

    if (text == NULL || literals == NULL || matched_literal == NULL ||
        match_position == NULL) {
        return 0;
    }

    *matched_literal = NULL;
    *match_position = SIZE_MAX;

    for (size_t i = 0; i < literal_count; ++i) {
        const char *match;

        if (literals[i] == NULL || literals[i][0] == '\0') {
            continue;
        }

        match = strstr(text, literals[i]);
        if (match != NULL) {
            size_t position = (size_t)(match - text);

            if (position < best_position ||
                (position == best_position && i < best_index)) {
                best_position = position;
                best_index = i;
            }
        }
    }

    if (best_index == SIZE_MAX) {
        return 0;
    }

    *matched_literal = literals[best_index];
    *match_position = best_position;
    return 1;
}

int main(int argc, char *argv[])
{
    const char *matched_literal;
    size_t match_position;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <text> <literal> [literal ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (find_literals(
            argv[1],
            (const char *const *)&argv[2],
            (size_t)(argc - 2),
            &matched_literal,
            &match_position) == 0) {
        puts("No match");
        return EXIT_SUCCESS;
    }

    if (printf("Found \"%s\" at position %zu\n",
               matched_literal,
               match_position) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}