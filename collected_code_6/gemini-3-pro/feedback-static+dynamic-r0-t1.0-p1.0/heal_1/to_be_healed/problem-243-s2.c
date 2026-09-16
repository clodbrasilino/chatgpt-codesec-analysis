#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Occurrence::value' is never used. [unusedStructMember]
     */
    int value;
    /* Possible weaknesses found:
     *  struct member 'Occurrence::count' is never used. [unusedStructMember]
     */
    int count;
} Occurrence;

int compareFirst(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    return tupleA->first - tupleB->first;
}

int countOccurrences(const Tuple *arr, int n, int value) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].first == value) {
            count++;
        }
    }
    return count;
}

int compareByOccurrence(const void *a, const void *b, void *arg) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    /* Possible weaknesses found:
     *  Variable 'arr' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *arr = (Tuple *)arg;
    int n = *((int *)arg - 1); 

    int countA = countOccurrences(arr, n, tupleA->first);
    int countB = countOccurrences(arr, n, tupleB->first);

    if (countA != countB) {
        return countA - countB; 
    }
    return tupleA->first - tupleB->first; 
}

void sortTuplesByOccurrence(Tuple *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    Tuple *temp = (Tuple *)malloc(n * sizeof(Tuple));
    if (temp == NULL) {
        return;
    }

    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int countA = countOccurrences(temp, n, arr[j].first);
            int countB = countOccurrences(temp, n, arr[j + 1].first);

            if (countA > countB || (countA == countB && arr[j].first > arr[j + 1].first)) {
                Tuple t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }

    free(temp);
}

int main(void) {
    Tuple arr[] = {
        {3, 1}, {2, 2}, {3, 3}, {1, 4}, {2, 5}, {3, 6}, {4, 7}
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    sortTuplesByOccurrence(arr, n);

    for (int i = 0; i < n; i++) {
        printf("(%d, %d) ", arr[i].first, arr[i].second);
    }
    printf("\n");

    return 0;
}