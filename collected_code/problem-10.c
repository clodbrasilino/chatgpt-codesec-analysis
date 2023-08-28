#include <stdio.h>

void getNSmallestItems(int dataset[], int n) {
    int smallest[n];
    int i, j, min, temp;
    
    for (i = 0; i < n; i++) {
        smallest[i] = dataset[i];
    }
    
    for (i = 0; i < n; i++) {
        min = i;
        
        for (j = i + 1; j < n; j++) {
            if (smallest[j] < smallest[min]) {
                min = j;
            }
        }
        
        temp = smallest[i];
        smallest[i] = smallest[min];
        smallest[min] = temp;
    }
    
    printf("The %d smallest items in the dataset are: ", n);
    
    for (i = 0; i < n; i++) {
        printf("%d ", smallest[i]);
    }
}

int main() {
    int dataset[] = {5, 10, 3, 15, 7};
    int n = 3;
    
    getNSmallestItems(dataset, n);
    
    return 0;
}