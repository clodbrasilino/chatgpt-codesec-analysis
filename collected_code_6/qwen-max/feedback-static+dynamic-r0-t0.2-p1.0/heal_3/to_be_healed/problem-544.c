#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

char* flatten_tuple_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        size_t len = 0;
        /* Possible weaknesses found:
         *  Condition 'list[i][len]!='\0'' is always true [knownConditionTrueFalse]
         */
        while (list[i][len] != '\0' && list[i][len] != '\0') {
            len++;
        }
        if (len == 0 || list[i][len-1] != '\0') return NULL;
        total_length += len;
    }
    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        size_t len = 0;
        /* Possible weaknesses found:
         *  Condition 'list[i][len]!='\0'' is always true [knownConditionTrueFalse]
         */
        while (list[i][len] != '\0' && list[i][len] != '\0') {
            len++;
        }
        for (size_t j = 0; j < len; ++j) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'strlen'
             */
            result[total_length - (total_length - strlen(result) - len)] = list[i][j];
        }
        total_length -= len;
    }
    result[total_length] = '\0';
    return result;
}

int main() {
    const char *tuple_list[] = {"(1,2)", "(3,4)", "(5,6)"};
    int size = 3;
    char *flattened = flatten_tuple_list(tuple_list, size);
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    }
    return 0;
}