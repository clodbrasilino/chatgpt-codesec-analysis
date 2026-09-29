#include <stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

int findFirstCommon(Tuple* tuples, int size){
    int i, j;

    for(i = 0; i < size; i++){
        for(j = i+1; j < size; j++){
            if(tuples[i].first == tuples[j].first){
                return tuples[i].first;
            }
        }
    }
    
    return -1; // Return -1 if no common element found
}

int main() {
    Tuple tuples[] = {{1,2}, {2,3}, {3,4}, {4,5}, {1,6}};
    int size = sizeof(tuples)/sizeof(tuples[0]);
    int common = findFirstCommon(tuples, size);

    if(common != -1) {
        printf("The first common element is: %d\n", common);
    } else {
        printf("No common first element found.\n");
    }

    return 0;
}