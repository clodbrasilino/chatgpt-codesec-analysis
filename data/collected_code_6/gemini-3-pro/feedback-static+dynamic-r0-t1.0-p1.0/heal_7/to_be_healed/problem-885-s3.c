#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    int map_s[256] = {0};
    int map_t[256] = {0};

    size_t i = 0;
    while (s[i] != '\0' && t[i] != '\0') {
        unsigned char char_s = (unsigned char)s[i];
        unsigned char char_t = (unsigned char)t[i];

        if (map_s[char_s] == 0 && map_t[char_t] == 0) {
            map_s[char_s] = char_t;
            map_t[char_t] = char_s;
        } else if (map_s[char_s] != char_t || map_t[char_t] != char_s) {
            return false;
        }
        i++;
    }

    if (s[i] != '\0' || t[i] != '\0') {
        return false;
    }

    return true;
}

int main(void) {
    size_t max_len = 10000;
    char *s = (char *)malloc(max_len * sizeof(char));
    char *t = (char *)malloc(max_len * sizeof(char));

    if (s == NULL || t == NULL) {
        free(s);
        free(t);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while (scanf("%9999s %9999s", s, t) == 2) {
        if (isIsomorphic(s, t)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }

    free(s);
    free(t);

    return EXIT_SUCCESS;
}