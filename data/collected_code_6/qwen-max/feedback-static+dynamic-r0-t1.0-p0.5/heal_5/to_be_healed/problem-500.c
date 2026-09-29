#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(const char *list[], size_t length) {
    if (length == 0) return NULL;

    size_t total_length = 1;
    for (size_t i = 0; i < length; ++i) {
        const char *ptr = list[i];
        if (!ptr) return NULL;
        
        size_t len = 0;
        /* Possible weaknesses found:
         *  Condition 'ptr[len]!='\0'' is always true [knownConditionTrueFalse]
         */
        while (ptr[len] && ptr[len] != '\0') len++;
        
        /* Possible weaknesses found:
         *  Assuming that condition 'len>1' is not redundant
         *  Condition 'len==1' is always true [knownConditionTrueFalse]
         *  Condition 'len==1' is always true
         *  Assuming that condition 'len>0' is not redundant
         */
        if (len > 0 && (len > 1 || (len == 1 && ptr[0] != '\0'))) {
            total_length += len;
        } else {
            return NULL;
        }
    }

    char *result = (char *)malloc(total_length);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (size_t i = 0, j = 0; i < length; ++i) {
        const char *ptr = list[i];
        if (!ptr) return NULL;
        
        size_t len = 0;
        /* Possible weaknesses found:
         *  Condition 'ptr[len]!='\0'' is always true [knownConditionTrueFalse]
         */
        while (ptr[len] && ptr[len] != '\0') len++;

        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + j, ptr, len);
            j += len;
        }
    }
    result[total_length - 1] = '\0';

    return result;
}

int main() {
    const char *list[] = {"Hello", " ", "World", "!"};
    size_t length = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, length);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid string detected\n");
    }

    return 0;
}