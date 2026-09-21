#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    
    char *concat1 = (char *)malloc(len1 + len2 + 1);
    char *concat2 = (char *)malloc(len1 + len2 + 1);
    
    if (!concat1 || !concat2) {
        free(concat1);
        free(concat2);
        exit(EXIT_FAILURE);
    }
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(concat1, str1);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(concat1, str2);
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(concat2, str2);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(concat2, str1);
    
    int result = strcmp(concat2, concat1);
    
    free(concat1);
    free(concat2);
    
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void printLargestNumber(int *arr, size_t n) {
    if (!arr || n == 0) {
        return;
    }
    
    char **strArr = (char **)malloc(n * sizeof(char *));
    if (!strArr) {
        exit(EXIT_FAILURE);
    }
    
    for (size_t i = 0; i < n; i++) {
        strArr[i] = (char *)malloc(12 * sizeof(char));
        if (!strArr[i]) {
            for (size_t j = 0; j < i; j++) {
                free(strArr[j]);
            }
            free(strArr);
            exit(EXIT_FAILURE);
        }
        snprintf(strArr[i], 12, "%d", arr[i]);
    }
    
    qsort(strArr, n, sizeof(char *), compare);
    
    if (strcmp(strArr[0], "0") == 0) {
        printf("0\n");
    } else {
        for (size_t i = 0; i < n; i++) {
            printf("%s", strArr[i]);
        }
        printf("\n");
    }
    
    for (size_t i = 0; i < n; i++) {
        free(strArr[i]);
    }
    free(strArr);
}

int main(void) {
    int arr[] = {3, 30, 34, 5, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    printLargestNumber(arr, n);
    
    return EXIT_SUCCESS;
}