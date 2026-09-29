#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

typedef struct {
    char *str;
} Element;

float str_to_float(const char *str) {
    char *endptr;
    float f = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') {
        return -1.0f;
    }
    return f;
}

void convert_list_to_float(Element *list, int size) {
    for (int i = 0; i < size; ++i) {
        float f = str_to_float(list[i].str);
        if (f != -1.0f) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char fstr[32];
            snprintf(fstr, sizeof(fstr), "%f", f);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(fstr);
            char *new_str = realloc(list[i].str, len + 1);
            if (new_str != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(new_str, fstr, len + 1);
                list[i].str = new_str;
            } else {
                perror("realloc failed");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main() {
    Element list[] = {{"123"}, {"456.789"}, {"abc"}, {"-123.456"}, {"0.123e2"}};
    int size = sizeof(list) / sizeof(list[0]);

    convert_list_to_float(list, size);

    for (int i = 0; i < size; ++i) {
        printf("%s\n", list[i].str);
    }

    for (int i = 0; i < size; ++i) {
        free(list[i].str);
    }

    return 0;
}