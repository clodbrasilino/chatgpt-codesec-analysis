#include <stdio.h>
#include <stdlib.h>

int list_to_single_int(const int *list, int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result = result * 10 + list[i];
    }
    return result;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    
    int result = list_to_single_int(numbers, length);
    
    printf("%d\n", result);
    
    return 0;
}