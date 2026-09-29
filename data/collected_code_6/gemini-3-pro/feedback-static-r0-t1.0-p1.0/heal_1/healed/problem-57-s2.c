#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (!str) return 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int compare(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    
    size_t len1 = safe_strlen(str1, 4096);
    size_t len2 = safe_strlen(str2, 4096);
    size_t total_len = len1 + len2 + 1;
    
    char *s1 = malloc(total_len);
    if (!s1) return 0;
    
    char *s2 = malloc(total_len);
    if (!s2) {
        free(s1);
        return 0;
    }
    
    snprintf(s1, total_len, "%s%s", str1, str2);
    snprintf(s2, total_len, "%s%s", str2, str1);
    
    int result = strncmp(s2, s1, total_len);
    
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