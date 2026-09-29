#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minRotations(char *str) {
    int n = strlen(str);
    if (n == 0) return 0;
    
    char *concat = (char *)malloc(2 * n + 1);
    if (concat == NULL) return -1;
    
    strcpy(concat, str);
    strcat(concat, str);
    
    char *temp = (char *)malloc(n + 1);
    if (temp == NULL) {
        free(concat);
        return -1;
    }
    
    for (int i = 1; i <= n; i++) {
        strncpy(temp, concat + i, n);
        temp[n] = '\0';
        if (strcmp(temp, str) == 0) {
            free(concat);
            free(temp);
            return i;
        }
    }
    
    free(concat);
    free(temp);
    return n;
}

int main() {
    char str[100];
    
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    
    int result = minRotations(str);
    printf("%d\n", result);
    
    return 0;
}