#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flattenTuple(int* tuple, int size) {
    char *str = (char*) calloc(20 * size, sizeof(char));

    if (str == NULL)
        return NULL;

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char num[20] = {0};
        snprintf(num, 20, "%d", tuple[i]);
        /* Possible weaknesses found:
         *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
         */
        strncat(str, num, 20);
        if (i < size - 1) {
            /* Possible weaknesses found:
             *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings. Risk is low because the source is a  constant character.
             */
            strncat(str, ",", 1);
        }
    }
    return str;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    char* result = flattenTuple(tuple, size);

    if (result == NULL) {
        printf("Memory allocation failed");
        return -1;
    }
    
    printf("%s\n", result);
    free(result);
    return 0;
}