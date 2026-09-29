#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 9
  *  test case 1 failed: expected 'Not Possible', got -1
  *  test case 0 failed: expected 1, got 0
  */

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);
    
    if (len1 != len2) {
        return -1;
    }
    
    int count1_s1 = 0, count1_s2 = 0;
    size_t i;
    
    for (i = 0; i < len1; i++) {
        if (s1[i] != '0' && s1[i] != '1') {
            return -1;
        }
        if (s2[i] != '0' && s2[i] != '1') {
            return -1;
        }
        if (s1[i] == '1') count1_s1++;
        if (s2[i] == '1') count1_s2++;
    }
    
    if (count1_s1 != count1_s2) {
        return -1;
    }
    
    int swaps = 0;
    int diff = 0;
    
    for (i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                diff++;
            } else {
                diff--;
            }
            if (diff > 0) {
                swaps += diff;
            }
        }
    }
    
    return swaps;
}

int main(void) {
    char *s1 = NULL;
    char *s2 = NULL;
    size_t len1 = 0;
    size_t len2 = 0;
    ssize_t read1, read2;
    
    read1 = getline(&s1, &len1, stdin);
    if (read1 == -1) {
        printf("Not Possible\n");
        free(s1);
        return 0;
    }
    
    read2 = getline(&s2, &len2, stdin);
    if (read2 == -1) {
        printf("Not Possible\n");
        free(s1);
        free(s2);
        return 0;
    }
    
    if (read1 > 0 && s1[read1 - 1] == '\n') {
        s1[read1 - 1] = '\0';
    }
    if (read2 > 0 && s2[read2 - 1] == '\n') {
        s2[read2 - 1] = '\0';
    }
    
    int result = min_swaps(s1, s2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
    
    free(s1);
    free(s2);
    
    return 0;
}