#include <stdio.h>
#include <string.h>

char* extract_rear_elements(char* arr[], int size) {
    static char rear_elements[100];
    int i;
    for(i = 0; i < size; i++) {
        int len = strlen(arr[i]);
        rear_elements[i] = arr[i][len - 1];
    }
    rear_elements[i] = '\0';
    return rear_elements;
}

int main() {
    char* arr[] = {"Hello", "World", "C", "Programming"};
    int size = sizeof(arr) / sizeof(arr[0]);
    char* rear_elements = extract_rear_elements(arr, size);
    printf("%s\n", rear_elements);
    return 0;
}