#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INPUT_LENGTH 4096

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t len = 0;

    if (str == NULL) {
        return 0;
    }

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    return len;
}

bool are_isomorphic(const char *str1, const char *str2)
{
    const size_t alphabet_size = (size_t)UCHAR_MAX + 1u;
    unsigned char *map_forward = NULL;
    bool *mapped_forward = NULL;
    bool *mapped_backward = NULL;
    size_t len1;
    size_t len2;
    size_t i;
    bool result = true;

    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    len1 = bounded_strlen(str1, MAX_INPUT_LENGTH);
    len2 = bounded_strlen(str2, MAX_INPUT_LENGTH);

    if (len1 >= MAX_INPUT_LENGTH || len2 >= MAX_INPUT_LENGTH) {
        return false;
    }

    if (len1 != len2) {
        return false;
    }

    map_forward = calloc(alphabet_size, sizeof(*map_forward));
    mapped_forward = calloc(alphabet_size, sizeof(*mapped_forward));
    mapped_backward = calloc(alphabet_size, sizeof(*mapped_backward));

    if (map_forward == NULL || mapped_forward == NULL || mapped_backward == NULL) {
        free(map_forward);
        free(mapped_forward);
        free(mapped_backward);
        return false;
    }

    for (i = 0; i < len1; i++) {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];

        if ((size_t)c1 >= alphabet_size || (size_t)c2 >= alphabet_size) {
            result = false;
            break;
        }

        if (mapped_forward[c1]) {
            if (map_forward[c1] != c2) {
                result = false;
                break;
            }
        } else {
            if (mapped_backward[c2]) {
                result = false;
                break;
            }
            map_forward[c1] = c2;
            mapped_forward[c1] = true;
            mapped_backward[c2] = true;
        }
    }

    free(map_forward);
    free(mapped_forward);
    free(mapped_backward);

    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        const char *program_name = (argc > 0 && argv[0] != NULL) ? argv[0] : "program";
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