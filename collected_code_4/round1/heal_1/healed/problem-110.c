#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

Range* getMissingRanges(int* array, int arraySize, int startRange, int endRange, int* missingSize) {
    int* rangeArray = calloc(endRange - startRange + 1, sizeof(int));
    if(rangeArray == NULL) {
        return NULL;
    }
    for(int i = 0; i < arraySize; i++) {
        if(array[i] >= startRange && array[i] <= endRange) {
            rangeArray[array[i]-startRange] = 1;
        }
    }

    int flag = 0;
    *missingSize = 0;
    for(int i = 0; i <= endRange - startRange; i++) {
        if(flag == 0 && rangeArray[i] == 0){
            (*missingSize)++;
            flag = 1;
        } else if(flag == 1 && rangeArray[i] == 1){
            flag = 0;
        }
    }

    Range* missingRanges = malloc(*missingSize * sizeof(Range));
    if(missingRanges == NULL) {
        free(rangeArray);
        return NULL;
    }
    int currentIndex = 0, flag2 = 0;
    for(int i = 0; i <= endRange - startRange; i++) {
        if(flag2 == 0 && rangeArray[i] == 0){
            missingRanges[currentIndex].start = i + startRange;
            flag2 = 1;
        } else if(flag2 == 1 && rangeArray[i] == 1){
            missingRanges[currentIndex].end = i + startRange - 1;
            flag2 = 0;
            currentIndex++;
        }
    }
    if(flag2 == 1) {
        missingRanges[currentIndex].end = endRange;
    }

    free(rangeArray);

    return missingRanges;
}

int main() {
    int array[] = {1, 3, 4, 7, 9, 10};
    int arraySize = sizeof(array) / sizeof(array[0]);
    int startRange = 1, endRange = 10;
    int missingSize = 0;

    Range* missingRanges = getMissingRanges(array, arraySize, startRange, endRange, &missingSize);

    if (missingRanges != NULL) {
        for(int i = 0; i < missingSize; i++) {
            printf("Missing Range is : %d - %d\n", missingRanges[i].start, missingRanges[i].end);
        }
        free(missingRanges);
    } else {
        printf("Could not allocate memory for missingRanges\n");
    }

    return 0;
}