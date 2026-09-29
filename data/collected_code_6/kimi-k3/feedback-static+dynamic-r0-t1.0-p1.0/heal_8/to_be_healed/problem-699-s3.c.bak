#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  *  test case 2 failed: expected 3, got 0
  *  test case 0 failed: expected 1, got 0
  */

int min_swaps(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    if (len1 != len2) {
        return -1;
    }
    
    int count1_s1 = 0, count1_s2 = 0;
    int i;
    
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
    
    int diff = 0;
    
    for (i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                diff++;
            } else {
                diff--;
            }
        }
    }
    
    return abs(diff);
}

int main(void) {
    char s1[1000], s2[1000];
    
    if (fgets(s1, sizeof(s1), stdin) == NULL) {
        return 1;
    }
    if (fgets(s2, sizeof(s2), stdin) == NULL) {
        return 1;
    }
    
    s1[strcspn(s1, "\n")] = '\0';
    s2[strcspn(s2, "\n")] = '\0';
    
    int result = min_swaps(s1, s2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}