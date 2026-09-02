#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
void find_values_greater_than(int *list, int list_size, int threshold) {
    for (int i = 0; i < list_size; i++) {
        if (list[i] > threshold) {
            printf("%d\n", list[i]);
        }
    }
}

int main() {
    int numbers[] = {10, 25, 30, 45, 5, 15, 60};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int threshold = 20;
    
    find_values_greater_than(numbers, size, threshold);
    
    return 0;
}