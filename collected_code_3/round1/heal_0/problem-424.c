#include <stdio.h>
#include <string.h>

char* extractRearIndex(char* arr[], int n) {
    static char result[100];
    int i;
    for(i = 0; i < n; i++) {
        int len = strlen(arr[i]);
        result[i] = arr[i][len - 1];
    }
    result[i] = '\0';
    return result;
}

int main() {
    char* arr[] = {"Hello", "World", "C", "Developer"};
    int n = sizeof(arr) / sizeof(arr[0]);
    char* result = extractRearIndex(arr, n);
    printf("%s\n", result);
    return 0;
}