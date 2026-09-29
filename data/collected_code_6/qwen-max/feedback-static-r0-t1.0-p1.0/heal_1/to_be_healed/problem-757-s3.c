#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_reverse_pairs(char **strs, int strCount) {
    int count = 0;
    for (int i = 0; i < strCount; ++i) {
        for (int j = i + 1; j < strCount; ++j) {
            char *str1 = strs[i];
            char *str2 = strs[j];
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            int len1 = strlen(str1);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            int len2 = strlen(str2);
            if (len1 == len2) {
                int match = 1;
                for (int k = 0; k < len1; ++k) {
                    if (str1[k] != str2[len2 - 1 - k]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    char *strs[] = {"abc", "cba", "xyz", "zyx", "123", "321"};
    int strCount = 6;
    printf("Number of reverse string pairs: %d\n", count_reverse_pairs(strs, strCount));
    return 0;
}