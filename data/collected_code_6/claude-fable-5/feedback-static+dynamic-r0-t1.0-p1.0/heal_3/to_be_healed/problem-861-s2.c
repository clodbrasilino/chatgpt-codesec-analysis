#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

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

static char *sorted_copy(const char *s)
{
    size_t len;
    size_t alloc_size;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    len = strnlen(s, MAX_STRING_LENGTH);
    if (len >= MAX_STRING_LENGTH) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    alloc_size = len + 1;
    copy = malloc(alloc_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         *  Condition 'len>=alloc_size' is always false [knownConditionTrueFalse]
         *  Condition 'len>=alloc_size' is always false
         */
        if (len >= alloc_size) {
            free(copy);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, s, len);
    }
    copy[len] = '\0';

    qsort(copy, len, sizeof(char), compare_chars);
    return copy;
}

int find_anagrams(const char *target, const char *const *list, size_t list_size,
                  size_t *result_indices, size_t *result_count)
{
    char *sorted_target;
    size_t target_len;
    size_t i;
    size_t count;

    if (target == NULL || list == NULL || result_indices == NULL ||
        result_count == NULL) {
        return -1;
    }

    *result_count = 0;

    target_len = strnlen(target, MAX_STRING_LENGTH);
    if (target_len >= MAX_STRING_LENGTH) {
        return -1;
    }

    sorted_target = sorted_copy(target);
    if (sorted_target == NULL) {
        return -1;
    }

    count = 0;
    for (i = 0; i < list_size; i++) {
        char *sorted_candidate;
        size_t candidate_len;

        if (list[i] == NULL) {
            continue;
        }

        candidate_len = strnlen(list[i], MAX_STRING_LENGTH);
        if (candidate_len >= MAX_STRING_LENGTH) {
            free(sorted_target);
            return -1;
        }

        if (candidate_len != target_len) {
            continue;
        }

        sorted_candidate = sorted_copy(list[i]);
        if (sorted_candidate == NULL) {
            free(sorted_target);
            return -1;
        }

        if (strcmp(sorted_candidate, sorted_target) == 0) {
            result_indices[count] = i;
            count++;
        }

        free(sorted_candidate);
    }

    free(sorted_target);
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
    size_t *indices;
    size_t found;
    size_t i;
    int status;

    indices = malloc(word_count * sizeof(size_t));
    if (indices == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = find_anagrams(target, words, word_count, indices, &found);
    if (status != 0) {
        fprintf(stderr, "Error while searching for anagrams\n");
        free(indices);
        return EXIT_FAILURE;
    }

    printf("Anagrams of \"%s\":\n", target);
    for (i = 0; i < found; i++) {
        printf("  %s\n", words[indices[i]]);
    }

    if (found == 0) {
        printf("  (none found)\n");
    }

    free(indices);
    return EXIT_SUCCESS;
}