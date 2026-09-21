#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATCHES 2U

int match_p_words(const char *const words[], size_t count,
                  const char *matches[], size_t max_matches,
                  size_t *found_count)
{
    size_t i;

    if (words == NULL || matches == NULL || found_count == NULL) {
        return -1;
    }

    if (max_matches == 0U) {
        return -1;
    }

    *found_count = 0U;

    for (i = 0U; i < count; i++) {
        if (words[i] == NULL) {
            return -1;
        }
        if ((words[i][0] == 'p') || (words[i][0] == 'P')) {
            if (*found_count < max_matches) {
                matches[*found_count] = words[i];
                (*found_count)++;
            }
            if (*found_count >= max_matches) {
                break;
            }
        }
    }

    return 0;
}

int main(void)
{
    const char *const word_list[] = {
        "apple", "pear", "banana", "peach", "grape", "plum"
    };
    size_t word_count = sizeof(word_list) / sizeof(word_list[0]);
    size_t matched_capacity = (size_t)MAX_MATCHES;
    size_t found = 0U;
    int status;

    const char **matched = calloc(matched_capacity, sizeof(*matched));
    if (matched == NULL) {
        if (fprintf(stderr, "Memory allocation failure.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    status = match_p_words(word_list, word_count, matched, matched_capacity, &found);
    if (status != 0) {
        free(matched);
        if (fprintf(stderr, "Error while matching words.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (found > matched_capacity) {
        free(matched);
        return EXIT_FAILURE;
    }

    if (found < matched_capacity) {
        if (printf("Fewer than %u words starting with 'p' were found.\n",
                   (unsigned int)matched_capacity) < 0) {
            free(matched);
            return EXIT_FAILURE;
        }
    } else {
        for (size_t i = 0U; i < found && i < matched_capacity; i++) {
            if (matched[i] == NULL) {
                free(matched);
                return EXIT_FAILURE;
            }
            if (printf("Match %zu: %s\n", i + 1U, matched[i]) < 0) {
                free(matched);
                return EXIT_FAILURE;
            }
        }
    }

    free(matched);
    return EXIT_SUCCESS;
}