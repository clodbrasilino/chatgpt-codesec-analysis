#include <stdio.h>

void findMissingRanges(const int* list, int size, int startRange, int endRange) {
    int i;
    
    printf("Missing Ranges: ");
    
    if (list[0] > startRange) {
        printf("%d-%d ", startRange, list[0] - 1);
    }
 
    for (i = 1; i < size; i++) {
        if (list[i] - list[i-1] > 1) {
            printf("%d-%d ", list[i-1] + 1, list[i] - 1);
        }
    }

    if (endRange > list[size-1]) {
        printf("%d-%d ", list[size-1] + 1, endRange);
    }
    
    printf("\n");
}

int main() {
    const int list[] = {4, 7, 10, 12, 15};
    int size = sizeof(list) / sizeof(list[0]);
    int startRange = 1;
    int endRange = 20;
    
    findMissingRanges(list, size, startRange, endRange);
    
    return 0;
}