#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool are_isomorphic(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    int map_forward[256];
    int map_backward[256];
    size_t i;

    if ((s1 == NULL) || (s2 == NULL)) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(s2);

    if (len1 != len2) {
        return false;
    }

    for (i = 0U; i < 256U; i++) {
        map_forward[i] = -1;
        map_backward[i] = -1;
    }

    for (i = 0U; i < len1; i++) {
        unsigned char c1 = (unsigned char)s1[i];
        unsigned char c2 = (unsigned char)s2[i];

        if ((map_forward[c1] == -1) && (map_backward[c2] == -1)) {
            map_forward[c1] = (int)c2;
            map_backward[c2] = (int)c1;
        } else if ((map_forward[c1] != (int)c2) || (map_backward[c2] != (int)c1)) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *test_pairs[][2] = {
        { "egg", "add" },
        { "foo", "bar" },
        { "paper", "title" },
        { "abc", "def" },
        { "ab", "aa" }
    };
    size_t num_pairs = sizeof(test_pairs) / sizeof(test_pairs[0]);
    size_t i;

    for (i = 0U; i < num_pairs; i++) {
        bool result = are_isomorphic(test_pairs[i][0], test_pairs[i][1]);
        if (printf("\"%s\" and \"%s\": %s\n",
                   test_pairs[i][0],
                   test_pairs[i][1],
                   result ? "isomorphic" : "not isomorphic") < 0) {
            return 1;
        }
    }

    return 0;
}