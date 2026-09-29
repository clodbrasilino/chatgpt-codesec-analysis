#include <stdio.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    if (len1 != len2) {
        return -1;
    }
    
    int count0_str1 = 0, count1_str1 = 0;
    int count0_str2 = 0, count1_str2 = 0;
    
    for (int i = 0; i < len1; i++) {
        if (str1[i] == '0') {
            count0_str1++;
        } else if (str1[i] == '1') {
            count1_str1++;
        } else {
            return -1;
        }
        
        if (str2[i] == '0') {
            count0_str2++;
        } else if (str2[i] == '1') {
            count1_str2++;
        } else {
            return -1;
        }
    }
    
    if (count0_str1 != count0_str2 || count1_str1 != count1_str2) {
        return -1;
    }
    
    int swaps = 0;
    int i = 0, j = 0;
    
    while (i < len1 && j < len2) {
        if (str1[i] == str2[j]) {
            i++;
            j++;
        } else {
            int k = i + 1;
            while (k < len1 && str1[k] == str1[i]) {
                k++;
            }
            
            if (k < len1) {
                swaps++;
                char temp = str1[i];
                ((char *)str1)[i] = str1[k];
                ((char *)str1)[k] = temp;
            } else {
                return -1;
            }
        }
    }
    
    return swaps;
}

int main() {
    char str1[100], str2[100];
    
    printf("Enter first binary string: ");
    if (scanf("%99s", str1) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter second binary string: ");
    if (scanf("%99s", str2) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = min_swaps(str1, str2);
    
    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    return 0;
}