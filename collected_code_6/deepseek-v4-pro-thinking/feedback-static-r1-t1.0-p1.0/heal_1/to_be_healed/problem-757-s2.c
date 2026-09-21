#include <stdio.h>
#include <string.h>

static int is_reverse(const char *a, const char *b)
{
    size_t la, lb, i;

    if (a == NULL || b == NULL) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    la = strlen(a);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    lb = strlen(b);
    if (la != lb) {
        return 0;
    }
    for (i = 0; i < la; ++i) {
        if (a[i] != b[lb - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

int count_reverse_pairs(const char *strs[], size_t n)
{
    int count = 0;
    size_t i, j;

    if (strs == NULL || n < 2) {
        return 0;
    }
    for (i = 0; i < n; ++i) {
        if (strs[i] == NULL) {
            continue;
        }
        for (j = i + 1; j < n; ++j) {
            if (strs[j] == NULL) {
                continue;
            }
            if (is_reverse(strs[i], strs[j])) {
                ++count;
            }
        }
    }
    return count;
}

int main(void)
{
    const char *strs[] = {"abc", "cba", "def", "fed", "hello", "olleh"};
    size_t n = sizeof(strs) / sizeof(strs[0]);

    printf("%d\n", count_reverse_pairs(strs, n));
    return 0;
}