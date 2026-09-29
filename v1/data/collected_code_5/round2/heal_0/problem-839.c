#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char first[MAX_SIZE];
    int second;
} Tuple;

int compare(const void* a, const void* b) {
    return strcmp(((Tuple*)a)->first, ((Tuple*)b)->first);
}

void sort_tuples(Tuple* tuples, size_t size) {
    qsort(tuples, size, sizeof(Tuple), compare);
}

int main() {
    size_t num_of_tuples = 5;
    Tuple tuples[] = { {"apple", 1}, {"orange", 2}, {"banana", 3}, {"mango", 4}, {"cherry", 5} };
    
    sort_tuples(tuples, num_of_tuples);
    
    for(size_t i = 0; i < num_of_tuples; i++) {
        printf("%s %d\n", tuples[i].first, tuples[i].second);
    }
    
    return 0;
}