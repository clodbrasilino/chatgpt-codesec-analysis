#include <stdio.h>
#include <string.h>

int arePermutations(const char* str1, const char* str2) {
    if(str1 == NULL || str2 == NULL) {
        return 0;
    }

    size_t len1 = strnlen(str1, 1024);
    size_t len2 = strnlen(str2, 1024);

    if (len1 != len2) {
        return 0;
    }

    int count[256] = {0};

    for (size_t i = 0; i < len1; i++) {
        count[(unsigned char)str1[i]]++;
    }

    for (size_t i = 0; i < len2; i++) {
        /* Possible weaknesses found:
         *  read of 1 byte from after the end of 'str2'
         *  valid subscripts for 'str2' are '[0]' to '[4]'
         *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         */
        count[(unsigned char)str2[i]]--;
    }

    for(int i = 0; i < 256; i++) {
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