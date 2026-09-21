#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;

StringTuple* concat_tuples(const StringTuple *t1, const StringTuple *t2) {
    if (!t1 || !t2 || !t1->first || !t1->second || !t2->first || !t2->second) {
        return NULL;
    }

    StringTuple *result = (StringTuple *)malloc(sizeof(StringTuple));
    if (!result) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(t1->first) + strlen(t2->first) + 1;
    result->first = (char *)malloc(len1);
    if (!result->first) {
        free(result);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(t1->second) + strlen(t2->second) + 1;
    result->second = (char *)malloc(len2);
    if (!result->second) {
        free(result->first);
        free(result);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result->first, t1->first);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(result->first, t2->first);

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result->second, t1->second);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(result->second, t2->second);

    return result;
}

void free_tuple(StringTuple *t) {
    if (t) {
        free(t->first);
        free(t->second);
        free(t);
    }
}

int main(void) {
    StringTuple t1 = {"Hello, ", "Open"};
    StringTuple t2 = {"World!", "AI"};

    StringTuple *result = concat_tuples(&t1, &t2);
    if (result) {
        printf("First: %s\n", result->first);
        printf("Second: %s\n", result->second);
        free_tuple(result);
    } else {
        printf("Concatenation failed.\n");
    }

    return 0;
}