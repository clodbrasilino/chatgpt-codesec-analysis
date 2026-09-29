#include <stdio.h>
#include <stdlib.h>

int count_even_elements(const int *list, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int n;
    
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n <= 0) {
        return 1;
    }
    
    int *list = (int *)malloc(n * sizeof(int));
    if (list == NULL) {
        return 1;
    }
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &list[i]) != 1) {
            free(list);
            return 1;
        }
    }
    
    int result = count_even_elements(list, n);
    printf("Number of even elements: %d\n", result);
    
    free(list);
    return 0;
}