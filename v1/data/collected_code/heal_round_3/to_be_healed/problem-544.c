#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strncat'
  */

char* flattenTuple(int* tuple, int size) {
    const int strSize = 20 * size;
    char *str = (char*) calloc(strSize, sizeof(char));

    if (str == NULL)
        return NULL;

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char num[20];
        snprintf(num, sizeof(num), "%d", tuple[i]);
        /* Possible weaknesses found:
         *  implicit declaration of function 'strncat' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'strncat' [-Wbuiltin-declaration-mismatch]
         *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
         *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
         *  include '<string.h>' or provide a declaration of 'strncat'
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  include '<string.h>' or provide a declaration of 'strlen'
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        strncat(str, num, strlen(num)<(size_t)(strSize-strlen(str)-1)?strlen(num):(strSize-strlen(str)-1));
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if (i < size - 1 && strSize-strlen(str)-1>0) {
            /* Possible weaknesses found:
             *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings. Risk is low because the source is a  constant character.
             *  'strncat' specified bound 1 equals source length [-Wstringop-overflow=]
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