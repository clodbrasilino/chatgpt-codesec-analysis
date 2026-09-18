#include<stdlib.h>
#include<stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void* a, const void* b)
{
    Tuple* t1 = (Tuple*)a;
    Tuple* t2 = (Tuple*)b;
    if (t1->first > t2->first) {
        return 1;
    } else if (t1->first < t2->first) {
        return -1;
    } else {
        if (t1->second > t2->second) {
            return 1;
        } else if (t1->second < t2->second) {
            return -1;
        } else {
            return 0;
        }
    }
}

void print_tuples(Tuple* arr, int size) {
    for(int i = 0; i < size; i++) {
        printf("(%d, %d)\n", arr[i].first, arr[i].second);
    }
}

int main() {
    Tuple arr[] = {{1, 2}, {3, 4}, {3, 1}, {2, 0}, {2, 3}};
    int size = sizeof(arr) / sizeof(Tuple);
    
    qsort(arr, size, sizeof(Tuple), compare);
    
    print_tuples(arr, size);
    
    return 0;
}