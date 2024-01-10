#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isTerminated(const char *str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t len = strlen(str);
    if(str[len] == '\0') {
        return true;
    }
    return false;
}

int minSwaps(const char str1[], const char str2[]) {
    if(!isTerminated(str1) || !isTerminated(str2)) {
        return -1;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len1 = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len2 = strlen(str2);
    
    if (len1 != len2) {
        return -1;
    }

    int count = 0;
    for (int i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            count++;
        }
    }

    return count / 2;
}

int main() {
    char str1[] = "010101";
    char str2[] = "101010";
    int swaps = minSwaps(str1, str2);
    printf("Minimum number of swaps required: %d\n", swaps);
    return 0;
}