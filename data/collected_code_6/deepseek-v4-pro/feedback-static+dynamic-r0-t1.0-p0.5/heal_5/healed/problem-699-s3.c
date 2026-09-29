#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps(const char *str1, const char *str2, size_t len) {
    int count0 = 0, count1 = 0;
    int swaps = 0;
    int mismatches = 0;

    if (str1 == NULL || str2 == NULL || len == 0) {
        return -1;
    }

    for (size_t i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            mismatches++;
            if (str1[i] == '0') {
                count0++;
            } else if (str1[i] == '1') {
                count1++;
            }
        }
    }

    if (count0 != count1) return -1;
    if (mismatches == 0) return 0;

    char *temp1 = malloc(len + 1);
    char *temp2 = malloc(len + 1);
    
    if (temp1 == NULL || temp2 == NULL) {
        free(temp1);
        free(temp2);
        return -1;
    }
    
    if (len > 0) {
        memcpy(temp1, str1, len);
        temp1[len] = '\0';
        memcpy(temp2, str2, len);
        temp2[len] = '\0';
    } else {
        free(temp1);
        free(temp2);
        return -1;
    }

    while (count0 > 0) {
        int pos0 = -1;
        int pos1 = -1;
        
        for (size_t i = 0; i < len; i++) {
            if (temp1[i] != temp2[i]) {
                if (temp1[i] == '0' && pos0 == -1) {
                    pos0 = (int)i;
                }
                if (temp1[i] == '1' && pos1 == -1) {
                    pos1 = (int)i;
                }
            }
        }

        if (pos0 == -1 || pos1 == -1) {
            break;
        }

        char tmp = temp1[pos0];
        temp1[pos0] = temp1[pos1];
        temp1[pos1] = tmp;
        
        swaps++;
        count0--;
    }

    free(temp1);
    free(temp2);
    
    return swaps;
}

int main(void) {
    char str1[102] = {0};
    char str2[102] = {0};

    printf("Enter first binary string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    size_t len1 = strlen(str1);
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }

    if (len1 > 100) {
        printf("Input string too long\n");
        return 1;
    }

    printf("Enter second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    size_t len2 = strlen(str2);
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }

    if (len2 > 100) {
        printf("Input string too long\n");
        return 1;
    }
    
    if (len1 != len2) {
        printf("Strings must be of equal length\n");
        return 1;
    }

    if (len1 == 0) {
        printf("Not Possible\n");
        return 0;
    }

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') {
            printf("First string must contain only 0 and 1\n");
            return 1;
        }
        if (str2[i] != '0' && str2[i] != '1') {
            printf("Second string must contain only 0 and 1\n");
            return 1;
        }
    }

    int result = min_swaps(str1, str2, len1);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}