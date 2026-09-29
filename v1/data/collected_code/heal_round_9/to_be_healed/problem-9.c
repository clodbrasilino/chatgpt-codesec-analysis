#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findMinRotations(const char* str) {
    if(str == NULL) 
        return -1;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t len =  strlen(str);
    if(len <= 0)
        return -1;    

    size_t size = (len*2) + 1;
    char* concat = (char*)calloc(size, sizeof(char));
    if(!concat) {
        printf("Memory Allocation Failed\n");
        return -1;
    }
    
    if (len > size) {
        printf("Length exceeds size\n");
        free(concat);
        return -1;      
    }

    if(len*2 >= size) {
        printf("Buffer overflow detected\n");
        free(concat);
        return -1;    
    }
   
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(concat, str, len);
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(concat + len, str, len);

    if(size <= len*2) {
        printf("Buffer overflow detected\n");
        free(concat);
        return -1; 
    }
   
    /* Possible weaknesses found:
     *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
     */
    concat[size - 1] = '\0';

    int rotations = 0;
    size_t k = 1;
    while(k < len) {
        size_t i = 0;
        size_t j = k;
        while(j < len * 2 && concat[i] <= concat[j]) {
            if(concat[i] < concat[j]) {
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
    
    if(minRotations != -1) 
        printf("Minimum number of rotations required: %d\n", minRotations);

    return 0;
}