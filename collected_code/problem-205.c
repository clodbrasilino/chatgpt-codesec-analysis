#include <stdio.h>
#define SIZE 100

typedef struct {
    int first;
    int second;
} Tuple;

int countInversions(Tuple tupleList[], int size) {
    int count = 0;
    
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (tupleList[i].first > tupleList[j].first) {
                count++;
            }
            if (tupleList[i].second > tupleList[j].second) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    Tuple tupleList[SIZE];
    int size;
    
    printf("Enter the size of the tuple list: ");
    scanf("%d", &size);
    
    printf("Enter the elements of the tuple list:\n");
    for (int i = 0; i < size; i++) {
        printf("Tuple %d: ", i + 1);
        scanf("%d %d", &tupleList[i].first, &tupleList[i].second);
    }
    
    int inversions = countInversions(tupleList, size);
    printf("Number of inversions: %d\n", inversions);
    
    return 0;
}