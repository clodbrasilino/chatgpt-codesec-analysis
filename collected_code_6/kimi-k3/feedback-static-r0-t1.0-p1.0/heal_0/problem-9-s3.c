#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minRotations(char *str) {
    int n = strlen(str);
    if (n == 0) return 0;
    
    int *concat = (int *)malloc(2 * n * sizeof(int));
    if (concat == NULL) return -1;
    
    for (int i = 0; i < 2 * n; i++) {
        concat[i] = str[i % n];
    }
    
    for (int i = 1; i <= n; i++) {
        int j;
        for (j = 0; j < n; j++) {
            if (concat[i + j] != str[j]) break;
        }
        if (j == n) {
            free(concat);
            return i;
        }
    }
    
    free(concat);
    return n;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    
    int result = minRotations(str);
    if (result >= 0) {
        printf("Minimum rotations: %d\n", result);
    } else {
        printf("Error occurred\n");
        return 1;
    }
    
    return 0;
}