#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_reverse(const char *str1, const char *str2)
{
    size_t len1;
    size_t len2;
    size_t i;

    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(str2);

    if (len1 != len2) {
        return 0;
    }

    for (i = 0; i < len1; i++) {
        if (str1[i] != str2[len1 - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

int count_reverse_pairs(const char *list[], size_t count)
{
    int pairs;
    size_t i;
    size_t j;

    if (list == NULL) {
        return 0;
    }

    pairs = 0;

    for (i = 0; i < count; i++) {
        if (list[i] == NULL) {
            continue;
        }
        for (j = i + 1; j < count; j++) {
            if (list[j] == NULL) {
                continue;
            }
            if (is_reverse(list[i], list[j])) {
                pairs++;
            }
        }
    }

    return pairs;
}

int main(void)
{
    const char *words[] = {"code", "edoc", "abc", "cba", "hello", "olleh", "test"};
    size_t count;
    int result;

    count = sizeof(words) / sizeof(words[0]);
    result = count_reverse_pairs(words, count);

    printf("Number of reverse string pairs: %d\n", result);

    return EXIT_SUCCESS;
}