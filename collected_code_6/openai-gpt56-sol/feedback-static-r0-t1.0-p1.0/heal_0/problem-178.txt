#include <stdio.h>
#include <string.h>

static int find_literal(const char *text, const char *const literals[], size_t count,
                        size_t *literal_index, size_t *position)
{
    size_t i;
    const char *match;
    const char *best_match = NULL;
    size_t best_index = 0;

    if (text == NULL || literals == NULL || literal_index == NULL || position == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (literals[i] == NULL || literals[i][0] == '\0') {
            return -1;
        }

        match = strstr(text, literals[i]);
        if (match != NULL && (best_match == NULL || match < best_match)) {
            best_match = match;
            best_index = i;
        }
    }

    if (best_match == NULL) {
        return 0;
    }

    *literal_index = best_index;
    *position = (size_t)(best_match - text);
    return 1;
}

int main(void)
{
    const char text[] = "The quick brown fox jumps over the lazy dog.";
    const char *const literals[] = {"fox", "dog", "cat"};
    const size_t count = sizeof literals / sizeof literals[0];
    size_t literal_index;
    size_t position;
    int result;

    result = find_literal(text, literals, count, &literal_index, &position);
    if (result < 0) {
        fputs("Invalid argument.\n", stderr);
        return 1;
    }

    if (result == 0) {
        puts("No literal found.");
        return 0;
    }

    if (printf("Found \"%s\" at position %zu.\n",
               literals[literal_index], position) < 0) {
        return 1;
    }

    return 0;
}