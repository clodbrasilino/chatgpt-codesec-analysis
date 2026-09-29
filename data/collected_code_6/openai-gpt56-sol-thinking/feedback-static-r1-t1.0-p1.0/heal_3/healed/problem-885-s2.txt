#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct character_mapping {
    unsigned char forward;
    unsigned char reverse;
    bool has_forward;
    bool has_reverse;
};

bool are_isomorphic(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    if ((uintmax_t)UCHAR_MAX >= (uintmax_t)SIZE_MAX) {
        return false;
    }

    const size_t mapping_count = (size_t)UCHAR_MAX + 1U;

    if (mapping_count > SIZE_MAX / sizeof(struct character_mapping)) {
        return false;
    }

    struct character_mapping *mappings =
        calloc(mapping_count, sizeof(*mappings));

    if (mappings == NULL) {
        return false;
    }

    bool result = true;

    while (*first != '\0' && *second != '\0') {
        const unsigned char left = (unsigned char)*first;
        const unsigned char right = (unsigned char)*second;

        if ((mappings[left].has_forward &&
             mappings[left].forward != right) ||
            (mappings[right].has_reverse &&
             mappings[right].reverse != left)) {
            result = false;
            break;
        }

        mappings[left].forward = right;
        mappings[left].has_forward = true;
        mappings[right].reverse = left;
        mappings[right].has_reverse = true;

        ++first;
        ++second;
    }

    if (result) {
        result = *first == '\0' && *second == '\0';
    }

    free(mappings);
    return result;
}

int main(int argc, char * const argv[])
{
    if (argc != 3) {
        const char *program =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr,
                    "Usage: %s <first-string> <second-string>\n",
                    program) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (puts(are_isomorphic(argv[1], argv[2]) ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}