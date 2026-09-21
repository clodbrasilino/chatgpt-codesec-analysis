#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096U

static int compare_chars(const void *a, const void *b)
{
    unsigned char ca = *(const unsigned char *)a;
    unsigned char cb = *(const unsigned char *)b;

    if (ca < cb) {
        return -1;
    }
    if (ca > cb) {
        return 1;
    }
    return 0;
}

static size_t bounded_length(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return 0U;
    }
    for (i = 0U; i < max_len; i++) {
        if (str[i] == '\0') {
            return i;
        }
    }
    return max_len;
}

static char *sorted_copy(const char *str)
{
    size_t len;
    char *copy;

    if (str == NULL) {
        return NULL;
    }

    len = bounded_length(str, MAX_STRING_LENGTH);
    if (len >= MAX_STRING_LENGTH) {
        return NULL;
    }

    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (len > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, str, len);
    }
    copy[len] = '\0';
    qsort(copy, len, sizeof(char), compare_chars);
    return copy;
}

int find_anagrams(const char *target, const char **list, size_t list_size,
                  size_t **result_indices, size_t *result_count)
{
    char *sorted_target;
    size_t *indices;
    size_t target_len;
    size_t count;
    size_t i;

    if (target == NULL || list == NULL || result_indices == NULL ||
        result_count == NULL) {
        return -1;
    }

    *result_indices = NULL;
    *result_count = 0U;

    target_len = bounded_length(target, MAX_STRING_LENGTH);
    if (target_len >= MAX_STRING_LENGTH) {
        return -1;
    }

    sorted_target = sorted_copy(target);
    if (sorted_target == NULL) {
        return -1;
    }

    if (list_size > (SIZE_MAX / sizeof(size_t))) {
        free(sorted_target);
        return -1;
    }

    indices = malloc(list_size * sizeof(size_t));
    if (indices == NULL && list_size > 0U) {
        free(sorted_target);
        return -1;
    }

    count = 0U;
    for (i = 0U; i < list_size; i++) {
        char *sorted_candidate;
        size_t candidate_len;

        if (list[i] == NULL) {
            continue;
        }

        candidate_len = bounded_length(list[i], MAX_STRING_LENGTH);
        if (candidate_len >= MAX_STRING_LENGTH) {
            continue;
        }
        if (candidate_len != target_len) {
            continue;
        }

        sorted_candidate = sorted_copy(list[i]);
        if (sorted_candidate == NULL) {
            free(indices);
            free(sorted_target);
            return -1;
        }

        if (strcmp(sorted_candidate, sorted_target) == 0) {
            indices[count] = i;
            count++;
        }

        free(sorted_candidate);
    }

    free(sorted_target);

    if (count == 0U) {
        free(indices);
        indices = NULL;
    }

    *result_indices = indices;
    *result_count = count;
    return 0;
}

int main(void)
{
    const char *target = "listen";
    const char *words[] = {
        "enlist",
        "google",
        "inlets",
        "banana",
        "silent",
        "tinsel",
        "listens"
    };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    size_t *matches = NULL;
    size_t match_count = 0U;
    size_t i;
    int rc;

    rc = find_anagrams(target, words, word_count, &matches, &match_count);
    if (rc != 0) {
        if (fprintf(stderr, "Error: failed to find anagrams\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Anagrams of \"%s\":\n", target) < 0) {
        free(matches);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < match_count; i++) {
        if (printf("  %s\n", words[matches[i]]) < 0) {
            free(matches);
            return EXIT_FAILURE;
        }
    }

    if (match_count == 0U) {
        if (printf("  (none found)\n") < 0) {
            free(matches);
            return EXIT_FAILURE;
        }
    }

    free(matches);
    return EXIT_SUCCESS;
}