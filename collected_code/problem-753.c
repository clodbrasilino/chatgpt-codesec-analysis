#include <stdio.h>

// Structure to represent a tuple
struct Tuple {
    int number;
    char name[50];
};

// Function to find minimum k records from tuple list
void findMinKRecords(struct Tuple tupleList[], int n, int k) {
    // Sort the tuple list in ascending order based on number
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tupleList[j].number > tupleList[j + 1].number) {
                struct Tuple temp = tupleList[j];
                tupleList[j] = tupleList[j + 1];
                tupleList[j + 1] = temp;
            }
        }
    }
    
    // Print the first k records
    for (int i = 0; i < k; i++) {
        printf("%d, %s\n", tupleList[i].number, tupleList[i].name);
    }
}

int main() {
    // Sample Tuple List
    struct Tuple tupleList[] = {
        {25, "John"},
        {12, "Jane"},
        {7, "Mike"},
        {18, "Sarah"},
        {30, "David"}
    };
    int n = sizeof(tupleList) / sizeof(tupleList[0]);
    int k = 3;

    // Find and print minimum k records
    findMinKRecords(tupleList, n, k);
    
    return 0;
}