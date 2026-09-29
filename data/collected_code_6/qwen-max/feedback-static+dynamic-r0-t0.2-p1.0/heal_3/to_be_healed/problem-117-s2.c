#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *str;
} Element;

float str_to_float(const char *str) {
    char *endptr;
    float f = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') {
        return -1.0f; // Indicate conversion failure
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
            char fstr[16];
            snprintf(fstr, sizeof(fstr), "%f", f);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            list[i].str = realloc(list[i].str, strlen(fstr) + 1);
            if (list[i].str != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                 */
                strcpy(list[i].str, fstr);
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