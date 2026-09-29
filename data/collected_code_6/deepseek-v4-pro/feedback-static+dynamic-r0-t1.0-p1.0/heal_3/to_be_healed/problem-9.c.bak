#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  */

int minRotations(char *str) {
    int n = strlen(str);
    if (n == 0) {
        return 0;
    }
    
    char *temp = (char *)malloc(2 * n + 1);
    if (temp == NULL) {
        return -1;
    }
    
    strcpy(temp, str);
    strcat(temp, str);
    
    int result = n;
    
    for (int i = 1; i < n; i++) {
        if (strncmp(str, temp + i, n) == 0) {
            result = i;
            break;
        }
    }
    
    free(temp);
    return result;
}

int main(void) {
    char str[100];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    
    if (strlen(str) == 0) {
        printf("Empty string\n");
        return 0;
    }
    
    int rotations = minRotations(str);
    if (rotations == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("%d\n", rotations);
    
    return 0;
}