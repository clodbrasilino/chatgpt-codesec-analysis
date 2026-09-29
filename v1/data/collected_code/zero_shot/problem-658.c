#include <stdio.h>

int findMaxOccurrences(int list[], int size) {
    int maxCount = 0;
    int maxItem = 0;
    
    for (int i = 0; i < size; i++) {
        int count = 0;
        
        for (int j = 0; j < size; j++) {
            if (list[j] == list[i]) {
                count++;
            }
        }
        
        if (count > maxCount) {
            maxCount = count;
            maxItem = list[i];
        }
    }
    
    return maxItem;
}

int main() {
    int list[] = {1, 2, 3, 4, 2, 3, 2, 1, 5, 2, 3};
    int size = sizeof(list) / sizeof(list[0]);
    
    int itemWithMaxOccurrences = findMaxOccurrences(list, size);
    
    printf("Item with maximum occurrences: %d\n", itemWithMaxOccurrences);
    
    return 0;
}