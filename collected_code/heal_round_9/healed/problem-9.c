#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 1024

int findMinRotations(const char* str) {
    if (str == NULL)
        return -1;

    size_t len = strlen(str);

    if (len <= 0)
        return -1;

    if (len > MAX_STRING_SIZE)
        return -1;

    size_t size = (len * 2) + 1;
    char* concat = (char*)calloc(size, sizeof(char));

    if (!concat) {
        printf("Memory Allocation Failed\n");
        return -1;
    }

    memcpy(concat, str, len < size ? len : size - 1);
    memcpy(concat + len, str, len < size - len - 1 ? len : size - len - 1);  

    concat[size - 1] = '\0';

    int rotations = 0;
    size_t k = 1;

    while (k < len) {
        size_t i = 0;
        size_t j = k;

        while (j < len * 2 && concat[i] <= concat[j]) {
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