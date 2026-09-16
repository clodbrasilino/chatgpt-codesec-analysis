#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    int m10 = 0;
    int m01 = 0;

    for (size_t i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '1' && s2[i] == '0') {
            m10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            m01++;
        }
    }

    if (m10 != m01) {
        return -1;
    }

    return m10;
}

int main(void) {
    char s1[100005];
    char s2[100005];
    
    /* Possible weaknesses found:
     *  scanf() without field width limits can crash with huge input data. [invalidscanf]
     */
    if (scanf("%s %s", s1, s2) == 2) {
        int result = min_swaps(s1, s2);
        
        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    }
    
    return 0;
}