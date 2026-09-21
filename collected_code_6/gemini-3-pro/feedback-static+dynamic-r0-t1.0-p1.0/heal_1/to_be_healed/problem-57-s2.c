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
    
    char *s1 = malloc(len1 + len2 + 1);
    if (!s1) return 0;
    
    char *s2 = malloc(len1 + len2 + 1);
    if (!s2) {
        free(s1);
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(s1, str1);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(s1, str2);
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(s2, str2);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(s2, str1);
    
    int result = strcmp(s2, s1);
    
    free(s1);
    free(s2);
    
    return result;
}

void printLargest(char **arr, int n) {
    if (arr == NULL || n <= 0) return;
    
    qsort(arr, n, sizeof(char *), compare);
    
    if (strcmp(arr[0], "0") == 0) {
        printf("0\n");
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            printf("%s", arr[i]);
        }
    }
    printf("\n");
}

int main(void) {
    char *arr[] = {"3", "30", "34", "5", "9"};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printLargest(arr, n);
    
    return 0;
}