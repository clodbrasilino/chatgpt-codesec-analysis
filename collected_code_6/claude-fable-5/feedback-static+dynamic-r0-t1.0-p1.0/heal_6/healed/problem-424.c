#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096U

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0U;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

static char *extract_rear(const char *const *strings, size_t count)
{
    char *result = NULL;
    size_t i;

    if (strings == NULL || count == 0U || count >= (SIZE_MAX - 1U)) {
        return NULL;
    }

    result = malloc(count + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        size_t len;

        if (strings[i] == NULL) {
            free(result);
            return NULL;
        }

        len = bounded_strlen(strings[i], MAX_STRING_LEN);
        if (len >= MAX_STRING_LEN) {
            free(result);
            return NULL;
        }

        if (len == 0U) {
            result[i] = ' ';
        } else {
            result[i] = strings[i][len - 1U];
        }
    }

    result[count] = '\0';
    return result;
}

static int print_rear(const char *rear, size_t count)
{
    size_t i;

    if (rear == NULL || count == 0U) {
        return -1;
    }

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        if (printf("'%c'", rear[i]) < 0) {
            return -1;
        }
        if (i + 1U < count) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
    }

    if (printf("]\n") < 0) {
        return -1;
    }

    if (fflush(stdout) != 0) {
        return -1;
    }

    return 0;
}

static int run_case(const char *const *words, size_t count)
{
    char *rear;
    int status;

    rear = extract_rear(words, count);
    if (rear == NULL) {
        (void)fprintf(stderr, "Extraction failed\n");
        return -1;
    }

    status = print_rear(rear, count);
    free(rear);

    if (status != 0) {
        (void)fprintf(stderr, "Printing failed\n");
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *const words0[] = { "Mers", "for", "Vers" };
    const char *const words1[] = { "Avenge", "for", "People" };
    const char *const words2[] = { "Gotta", "get", "go" };

    if (run_case(words0, sizeof(words0) / sizeof(words0[0])) != 0) {
        return EXIT_FAILURE;
    }

    if (run_case(words1, sizeof(words1) / sizeof(words1[0])) != 0) {
        return EXIT_FAILURE;
    }

    if (run_case(words2, sizeof(words2) / sizeof(words2[0])) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}