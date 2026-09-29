#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;

StringTuple* concatenate_tuples(const StringTuple *tuple1, const StringTuple *tuple2) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return NULL;
    }

    if (tuple1->first == NULL || tuple1->second == NULL || 
        tuple2->first == NULL || tuple2->second == NULL) {
        return NULL;
    }

    StringTuple *result = (StringTuple *)malloc(sizeof(StringTuple));
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(tuple1->first) + strlen(tuple2->first) + 1;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(tuple1->second) + strlen(tuple2->second) + 1;

    result->first = (char *)malloc(len1);
    if (result->first == NULL) {
        free(result);
        return NULL;
    }

    result->second = (char *)malloc(len2);
    if (result->second == NULL) {
        free(result->first);
        free(result);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result->first, tuple1->first);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(result->first, tuple2->first);

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result->second, tuple1->second);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(result->second, tuple2->second);

    return result;
}

void free_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        if (tuple->first != NULL) {
            free(tuple->first);
        }
        if (tuple->second != NULL) {
            free(tuple->second);
        }
        free(tuple);
    }
}

int main(void) {
    StringTuple t1 = {"Hello", "Open"};
    StringTuple t2 = {"World", "AI"};

    StringTuple *result = concatenate_tuples(&t1, &t2);

    if (result != NULL) {
        printf("First: %s\n", result->first);
        printf("Second: %s\n", result->second);
        free_tuple(result);
    } else {
        printf("Failed to concatenate tuples.\n");
    }

    return 0;
}