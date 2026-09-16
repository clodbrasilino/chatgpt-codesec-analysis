#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool are_isomorphic(const char *str1, const char *str2)
{
    unsigned char map_forward[256] = {0};
    unsigned char map_backward[256] = {0};
    bool mapped_forward[256] = {false};
    bool mapped_backward[256] = {false};
    size_t len1;
    size_t len2;
    size_t i;

    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 != len2) {
        return false;
    }

    for (i = 0; i < len1; i++) {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];

        if (mapped_forward[c1]) {
            if (map_forward[c1] != c2) {
                return false;
            }
        } else {
            if (mapped_backward[c2]) {
                return false;
            }
            map_forward[c1] = c2;
            /* Possible weaknesses found:
             *  Variable 'map_backward[c2]' is assigned a value that is never used. [unreadVariable]
             */
            map_backward[c2] = c1;
            mapped_forward[c1] = true;
            mapped_backward[c2] = true;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     *  The scope of the variable 'program_name' can be reduced. [variableScope]
     */
    const char *program_name;

    if (argc != 3) {
        program_name = (argc > 0 && argv[0] != NULL) ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return EXIT_FAILURE;
    }

    if (are_isomorphic(argv[1], argv[2])) {
        printf("\"%s\" and \"%s\" are isomorphic.\n", argv[1], argv[2]);
    } else {
        printf("\"%s\" and \"%s\" are not isomorphic.\n", argv[1], argv[2]);
    }

    return EXIT_SUCCESS;
}