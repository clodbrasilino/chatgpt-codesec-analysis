#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 1024

int findMinRotations(const char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if (str == NULL || strlen(str) == 0 || strlen(str) > MAX_STRING_SIZE) 
        return -1;
        
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t len = strlen(str);
    size_t size = len * 2;
    char* concat = (char*)calloc(size, sizeof(char));

    if (!concat) {
        printf("Memory Allocation Failed\n");
        return -1;
    }

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(concat, str, len);
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(concat + len, str, len);
    concat[size - 1] = '\0';

    int rotations = 0;
    size_t k = 1;

    while (k < len) {
        size_t i = 0;
        size_t j = k;

        while (j < len * 2 - 1 && concat[i] <= concat[j]) {
            if (concat[i] < concat[j]) {
                rotations = k;
                break;
            }
            i++;
            j++;
        }
        k++;
    }

    free(concat);
    
    return rotations;
}

int main() {
    const char* str = "abcd";
    int minRotations = findMinRotations(str);

    if (minRotations != -1) 
        printf("Minimum number of rotations required: %d\n", minRotations);

    return 0;
}