#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

Range* getMissingRanges(int* array, int arraySize, int startRange, int endRange, int* missingSize) {
    int* rangeArray = calloc(endRange - startRange + 1, sizeof(int));
    for(int i = 0; i < arraySize; i++) {
        if(array[i] >= startRange && array[i] <= endRange) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'rangeArray' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            rangeArray[array[i]-startRange] = 1;
        }
    }

    int flag = 0;
    *missingSize = 0;
    for(int i = 0; i <= endRange - startRange; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'rangeArray' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        if(flag == 0 && rangeArray[i] == 0){
            (*missingSize)++;
            flag = 1;
        } else if(flag == 1 && rangeArray[i] == 1){
            flag = 0;
        }
    }

    Range* missingRanges = malloc(*missingSize * sizeof(Range));
    int currentIndex = 0, flag2 = 0;
    for(int i = 0; i <= endRange - startRange; i++) {
        if(flag2 == 0 && rangeArray[i] == 0){
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'missingRanges' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
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

    for(int i = 0; i < missingSize; i++) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*missingRanges_24 + _2.end' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of possibly-NULL 'missingRanges' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        printf("Missing Range is : %d - %d\n", missingRanges[i].start, missingRanges[i].end);
    }

    free(missingRanges);

    return 0;
}