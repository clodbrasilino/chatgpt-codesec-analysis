#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['a', 't', 'o'], got <no output>
  *  test case 0 failed: expected ['s', 'r', 's'], got <no output>
  *  test case 1 failed: expected ['e', 'r', 'e'], got <no output>
  */

char *extract_rear(const char *const *strings, size_t count)
{
    char *result;
    size_t i;

    if (strings == NULL || count == 0U) {
        return NULL;
    }

    result = (char *)malloc(count + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        size_t len;

        if (strings[i] == NULL) {
            free(result);
            return NULL;
        }

        len = strlen(strings[i]);
        if (len == 0U) {
            result[i] = ' ';
        } else {
            result[i] = strings[i][len - 1U];
        }
    }

    result[count] = '\0';
    return result;
}

int print_rear(const char *rear, size_t count)
{
    size_t i;

    if (rear == NULL) {
        return -1;
    }

    if (fputs("[", stdout) == EOF) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        if (printf("'%c'", rear[i]) < 0) {
            return -1;
        }
        if (i + 1U < count) {
            if (fputs(", ", stdout) == EOF) {
                return -1;
            }
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    if (fflush(stdout) != 0) {
        return -1;
    }

    return 0;
}

int run_case(const char *const *words, size_t count)
{
    char *rear;
    int status;

    rear = extract_rear(words, count);
    if (rear == NULL) {
        fprintf(stderr, "Failed to extract rear elements\n");
        return -1;
    }

    status = print_rear(rear, count);
    free(rear);

    return status;
}

int main(void)
{
    const char *const words0[] = { "Mers", "for", "Vers" };
    const char *const words1[] = { "blue", "star", "tree" };
    const char *const words2[] = { "pizza", "cat", "hello" };

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