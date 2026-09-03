#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

typedef struct {
    Range *ranges;
    int count;
    int capacity;
} RangeList;

void initRangeList(RangeList *list) {
    list->ranges = NULL;
    list->count = 0;
    list->capacity = 0;
}

int addRange(RangeList *list, int start, int end) {
    if (list->count >= list->capacity) {
        int newCapacity = list->capacity == 0 ? 8 : list->capacity * 2;
        Range *newRanges = (Range *)realloc(list->ranges, newCapacity * sizeof(Range));
        if (newRanges == NULL) {
            return 0;
        }
        list->ranges = newRanges;
        list->capacity = newCapacity;
    }
    list->ranges[list->count].start = start;
    list->ranges[list->count].end = end;
    list->count++;
    return 1;
}

void freeRangeList(RangeList *list) {
    free(list->ranges);
    list->ranges = NULL;
    list->count = 0;
    list->capacity = 0;
}

int compareRanges(const void *a, const void *b) {
    const Range *rangeA = (const Range *)a;
    const Range *rangeB = (const Range *)b;
    if (rangeA->start != rangeB->start) {
        return rangeA->start - rangeB->start;
    }
    return rangeA->end - rangeB->end;
}

/* Possible weaknesses found:
 *  Parameter 'ranges' can be declared as pointer to const [constParameterPointer]
 */
RangeList findMissingRanges(Range *ranges, int rangeCount, int startRange, int endRange) {
    RangeList missing;
    initRangeList(&missing);
    
    if (rangeCount == 0) {
        if (startRange <= endRange) {
            if (!addRange(&missing, startRange, endRange)) {
                freeRangeList(&missing);
            }
        }
        return missing;
    }
    
    Range *sortedRanges = (Range *)malloc(rangeCount * sizeof(Range));
    if (sortedRanges == NULL) {
        return missing;
    }
    
    for (int i = 0; i < rangeCount; i++) {
        sortedRanges[i] = ranges[i];
    }
    
    qsort(sortedRanges, rangeCount, sizeof(Range), compareRanges);
    
    int current = startRange;
    
    for (int i = 0; i < rangeCount; i++) {
        if (sortedRanges[i].end < current) {
            continue;
        }
        
        if (sortedRanges[i].start > current) {
            int missingEnd = sortedRanges[i].start - 1;
            if (missingEnd > endRange) {
                missingEnd = endRange;
            }
            if (current <= missingEnd) {
                if (!addRange(&missing, current, missingEnd)) {
                    free(sortedRanges);
                    freeRangeList(&missing);
                    return missing;
                }
            }
            current = sortedRanges[i].end + 1;
        } else {
            if (sortedRanges[i].end + 1 > current) {
                current = sortedRanges[i].end + 1;
            }
        }
        
        if (current > endRange) {
            break;
        }
    }
    
    if (current <= endRange) {
        if (!addRange(&missing, current, endRange)) {
            free(sortedRanges);
            freeRangeList(&missing);
            return missing;
        }
    }
    
    free(sortedRanges);
    return missing;
}

int main(void) {
    Range ranges[] = {
        {2, 5},
        {8, 10},
        {15, 20},
        {25, 30}
    };
    int rangeCount = sizeof(ranges) / sizeof(ranges[0]);
    int startRange = 1;
    int endRange = 35;
    
    RangeList missing = findMissingRanges(ranges, rangeCount, startRange, endRange);
    
    printf("Missing ranges from %d to %d:\n", startRange, endRange);
    for (int i = 0; i < missing.count; i++) {
        printf("[%d, %d]\n", missing.ranges[i].start, missing.ranges[i].end);
    }
    
    freeRangeList(&missing);
    
    Range emptyRanges[] = {};
    RangeList emptyMissing = findMissingRanges(emptyRanges, 0, 5, 10);
    
    printf("\nMissing ranges with empty input from 5 to 10:\n");
    for (int i = 0; i < emptyMissing.count; i++) {
        printf("[%d, %d]\n", emptyMissing.ranges[i].start, emptyMissing.ranges[i].end);
    }
    
    freeRangeList(&emptyMissing);
    
    Range overlappingRanges[] = {
        {1, 5},
        {3, 8},
        {7, 12},
        {15, 18}
    };
    int overlappingCount = sizeof(overlappingRanges) / sizeof(overlappingRanges[0]);
    
    RangeList overlappingMissing = findMissingRanges(overlappingRanges, overlappingCount, 1, 20);
    
    printf("\nMissing ranges with overlapping input from 1 to 20:\n");
    for (int i = 0; i < overlappingMissing.count; i++) {
        printf("[%d, %d]\n", overlappingMissing.ranges[i].start, overlappingMissing.ranges[i].end);
    }
    
    freeRangeList(&overlappingMissing);
    
    return 0;
}