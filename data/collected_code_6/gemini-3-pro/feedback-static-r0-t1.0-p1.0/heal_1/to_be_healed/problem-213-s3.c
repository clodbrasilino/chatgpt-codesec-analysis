#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* str1;
    char* str2;
} StringTuple;

StringTuple* concatenate_tuples(const StringTuple* t1, const StringTuple* t2) {
    if (!t1 || !t2 || !t1->str1 || !t1->str2 || !t2->str1 || !t2->str2) {
        return NULL;
    }

    StringTuple* result = (StringTuple*)malloc(sizeof(StringTuple));
    if (!result) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1_1 = strlen(t1->str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2_1 = strlen(t2->str1);
    result->str1 = (char*)malloc(len1_1 + len2_1 + 1);
    if (!result->str1) {
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result->str1, t1->str1, len1_1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result->str1 + len1_1, t2->str1, len2_1 + 1);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1_2 = strlen(t1->str2);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2_2 = strlen(t2->str2);
    result->str2 = (char*)malloc(len1_2 + len2_2 + 1);
    if (!result->str2) {
        free(result->str1);
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result->str2, t1->str2, len1_2);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result->str2 + len1_2, t2->str2, len2_2 + 1);

    return result;
}

void free_tuple(StringTuple* t) {
    if (t) {
        if (t->str1) {
            free(t->str1);
        }
        if (t->str2) {
            free(t->str2);
        }
        free(t);
    }
}

int main(void) {
    StringTuple t1 = {"Hello, ", "Good "};
    StringTuple t2 = {"World!", "Morning!"};

    StringTuple* result = concatenate_tuples(&t1, &t2);
    if (result) {
        printf("Result Tuple: (%s, %s)\n", result->str1, result->str2);
        free_tuple(result);
    } else {
        printf("Failed to concatenate tuples.\n");
    }

    return 0;
}