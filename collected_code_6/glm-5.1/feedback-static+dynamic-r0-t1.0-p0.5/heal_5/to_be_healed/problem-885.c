#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

bool isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_s = strlen(s);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_t = strlen(t);

    if (len_s != len_t) {
        return false;
    }

    if (len_s == 0) {
        return true;
    }

    int map_s_to_t[256] = {0};
    int map_t_to_s[256] = {0};

    for (size_t i = 0; i < len_s; i++) {
        unsigned char char_s = (unsigned char)s[i];
        unsigned char char_t = (unsigned char)t[i];

        if (map_s_to_t[char_s] == 0 && map_t_to_s[char_t] == 0) {
            map_s_to_t[char_s] = char_t + 1;
            map_t_to_s[char_t] = char_s + 1;
        } else {
            if (map_s_to_t[char_s] != char_t + 1 || map_t_to_s[char_t] != char_s + 1) {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }

    bool result = isIsomorphic(argv[1], argv[2]);

    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}