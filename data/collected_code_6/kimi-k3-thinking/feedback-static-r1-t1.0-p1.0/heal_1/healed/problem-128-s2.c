#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t bounded_strnlen(const char *s, size_t maxlen)
{
    const char *end;

    if (s == NULL) {
        return 0;
    }

    end = memchr(s, '\0', maxlen);
    if (end == NULL) {
        return maxlen;
    }
    return (size_t)(end - s);
}

static char **shortlist_words(char *const words[], size_t count, size_t n, size_t *out_count)
{
    char **result;
    size_t i;
    size_t j;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (words == NULL) {
        return NULL;
    }

    result = malloc((count > 0 ? count : 1) * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < count; i++) {
        if (words[i] != NULL && bounded_strnlen(words[i], n + 1) > n) {
            result[j] = words[i];
            j++;
        }
    }

    *out_count = j;
    return result;
}

int main(void)
{
    char *words[] = {"apple", "banana", "kiwi", "strawberry", "fig", "cherry"};
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t n = 4;
    size_t shortlisted_count = 0;
    char **shortlisted;
    size_t i;

    shortlisted = shortlist_words(words, count, n, &shortlisted_count);
    if (shortlisted == NULL) {
        fprintf(stderr, "Error: unable to shortlist words\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < shortlisted_count; i++) {
        printf("%s\n", shortlisted[i]);
    }

    free(shortlisted);
    return EXIT_SUCCESS;
}