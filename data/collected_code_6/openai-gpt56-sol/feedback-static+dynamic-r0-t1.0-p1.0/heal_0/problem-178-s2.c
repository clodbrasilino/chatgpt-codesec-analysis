#include <stdio.h>
#include <string.h>

static int find_first_literal(const char *text,
                              const char *const literals[],
                              size_t literal_count,
                              size_t *literal_index,
                              size_t *position)
{
    size_t best_position = 0;
    size_t best_index = 0;
    int found = 0;

    if (text == NULL || literals == NULL ||
        literal_index == NULL || position == NULL) {
        return -1;
    }

    for (size_t i = 0; i < literal_count; ++i) {
        const char *match;

        if (literals[i] == NULL) {
            return -1;
        }

        match = strstr(text, literals[i]);
        if (match != NULL) {
            size_t current_position = (size_t)(match - text);

            if (!found || current_position < best_position) {
                best_position = current_position;
                best_index = i;
                found = 1;
            }
        }
    }

    if (found) {
        *literal_index = best_index;
        *position = best_position;
    }

    return found;
}

int main(void)
{
    const char text[] = "The quick brown fox jumps over the lazy dog.";
    const char *const literals[] = {
        "brown",
        "lazy",
        "cat"
    };
    size_t literal_index = 0;
    size_t position = 0;
    int result = find_first_literal(
        text,
        literals,
        sizeof(literals) / sizeof(literals[0]),
        &literal_index,
        &position
    );

    if (result < 0) {
        fputs("Invalid argument.\n", stderr);
        return 1;
    }

    if (result == 0) {
        puts("No literal found.");
        return 0;
    }

    if (printf("Found \"%s\" at position %zu.\n",
               literals[literal_index],
               position) < 0) {
        return 1;
    }

    return 0;
}