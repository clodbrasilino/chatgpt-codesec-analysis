#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

int compare(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    
    if (!str1 || !str2) return 0;

    size_t len1 = 0;
    while (len1 < MAX_STR_LEN && str1[len1] != '\0') {
        len1++;
    }
    
    size_t len2 = 0;
    while (len2 < MAX_STR_LEN && str2[len2] != '\0') {
        len2++;
    }
    
    size_t total_size = len1 + len2 + 1;
    
    char *s1 = malloc(total_size);
    if (!s1) return 0;
    
    char *s2 = malloc(total_size);
    if (!s2) {
        free(s1);
        return 0;
    }
    
    snprintf(s1, total_size, "%s%s", str1, str2);
    snprintf(s2, total_size, "%s%s", str2, str1);
    
    int result = strcmp(s2, s1);
    
    free(s1);
    free(s2);
    
    return result;
}

void printLargest(char **arr, int n) {
    if (arr == NULL || n <= 0) return;
    
    qsort(arr, n, sizeof(char *), compare);
    
    if (strncmp(arr[0], "0", 2) == 0) {
        printf("0\n");
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            printf("%s", arr[i]);
        }
    }
    printf("\n");
}

int main(void) {
    char *arr[] = {"3", "30", "34", "5", "9"};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printLargest(arr, n);
    
    return 0;
}