```
#include<stdio.h>

int countElementsBefore(int tuple[], int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (tuple[i] == value) {
            return count;
        }
        count++;
    }
    return -1; // If value doesn't exist in the tuple.
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(tuple)/sizeof(int);

    int value = 4;
    int result = countElementsBefore(tuple, size, value);

    if(result == -1) {
        printf("%d does not exist in the tuple.", value);
    } else {
        printf("Number of elements before %d in the tuple is: %d", value, result);
    }
    
    return 0;
}