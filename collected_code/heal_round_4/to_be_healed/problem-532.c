#include <stdio.h>
#include <string.h>

int arePermutations(const char* str1, const char* str2) {
    if(str1 == NULL || str2 == NULL)
        return 0;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len1 = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len2 = strlen(str2);

    if (len1 != len2)
        return 0;

    int count[256] = {0};

    for (int i = 0; i < len1; i++) {
        count[(unsigned char)str1[i]]++;
    }

    for (int i = 0; i < len2; i++) {
        /* Possible weaknesses found:
         *  valid subscripts for 'str2' are '[0]' to '[4]'
         *  read of 1 byte from after the end of 'str2'
         *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         */
        count[(unsigned char)str2[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] != 0)
            return 0;
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