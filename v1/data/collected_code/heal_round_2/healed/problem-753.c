#include <stdio.h>
#include <string.h>

// Structure to represent a tuple
struct Tuple {
    int number;
    char name[51];
};

// Function to find minimum k records from tuple list
void findMinKRecords(struct Tuple tupleList[], int n, int k) {
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tupleList[j].number > tupleList[j + 1].number) {
                struct Tuple temp = {0, ""};

                if (sizeof(struct Tuple) <= sizeof(temp)) {
                    memcpy(&temp, &tupleList[j], sizeof(struct Tuple));
                }
                
                if (sizeof(struct Tuple) <= sizeof(tupleList[j])) {
                    memcpy(&tupleList[j], &tupleList[j + 1], sizeof(struct Tuple));
                }
                
                if (sizeof(struct Tuple) <= sizeof(tupleList[j + 1])) {
                    memcpy(&tupleList[j + 1], &temp, sizeof(struct Tuple));
                }
            }
        }
    }
    
    for (int i = 0; i < k && i < n; i++) {
        printf("%d, %s\n", tupleList[i].number, tupleList[i].name);
    }
}

int main() {
    struct Tuple tupleList[] = {
        {25, "John"},
        {12, "Jane"},
        {7, "Mike"},
        {18, "Sarah"},
        {30, "David"},
    };
    int n = sizeof(tupleList) / sizeof(tupleList[0]);
    int k = 3;

    findMinKRecords(tupleList, n, k);
    
    return 0;
}