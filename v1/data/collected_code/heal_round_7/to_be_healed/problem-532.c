#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_STR_LENGTH 1024

int arePermutations(const char* str1, const char* str2) {
    
    if(str1 == NULL || str2 == NULL) {
        return 0;
    }

    size_t len1 = strnlen(str1, MAX_STR_LENGTH);
    size_t len2 = strnlen(str2, MAX_STR_LENGTH);

    if (len1 != len2 || len1 >= MAX_STR_LENGTH || len2 >= MAX_STR_LENGTH) {
        return 0;
    }

    int count[UCHAR_MAX] = {0};

    for(size_t i = 0; i < len1; i++) {
        count[(unsigned char)str1[i]]++;
    }

    for(size_t i = 0; i < len2; i++) {
        /* Possible weaknesses found:
         *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         *  valid subscripts for 'str2' are '[0]' to '[4]'
         *  read of 1 byte from after the end of 'str2'
         */
        count[(unsigned char)str2[i]]--;
    }

    for(int i = 0; i < UCHAR_MAX; i++) {
        if (count[i] != 0) {
            return 0;
        }
    }

    return 1;
}

int main() {

    const char str1[] = "abcd";
    const char str2[] = "dcba";

    if (arePermutations(str1, str2)) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }

    return 0;
}