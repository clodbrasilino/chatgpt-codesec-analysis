#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATCHES 2

int match_p_words(const char *const words[], size_t count,
                  const char *matches[], size_t max_matches,
                  size_t *found_count)
{
    if (words == NULL || matches == NULL || found_count == NULL) {
        return -1;
    }

    *found_count = 0U;

    if (max_matches == 0U) {
        return 0;
    }

    for (size_t i = 0U; i < count; i++) {
        if (words[i] == NULL) {
            return -1;
        }
        if ((words[i][0] == 'p') || (words[i][0] == 'P')) {
            if (*found_count < max_matches) {
                matches[*found_count] = words[i];
                (*found_count)++;
            }
            if (*found_count == max_matches) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *matched[MAX_MATCHES] = { NULL, NULL };
    size_t word_count = sizeof(word_list) / sizeof(word_list[0]);
    size_t matched_capacity = sizeof(matched) / sizeof(matched[0]);
    size_t found = 0U;
    int status;

    status = match_p_words(word_list, word_count, matched,
                           matched_capacity, &found);
    if (status != 0) {
        if (fprintf(stderr, "Error while matching words.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (found > matched_capacity) {
        return EXIT_FAILURE;
    }

    if (found < matched_capacity) {
        if (printf("Fewer than %d words starting with 'p' were found.\n",
                   MAX_MATCHES) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        for (size_t i = 0U; i < found && i < matched_capacity; i++) {
            if (matched[i] == NULL) {
                return EXIT_FAILURE;
            }
            if (printf("Match %zu: %s\n", i + 1U, matched[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}