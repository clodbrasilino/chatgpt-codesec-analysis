#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int first;
    int second;
} pair;

void find_symmetric_pairs(pair* arr, int n) {
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(arr[i].first == arr[j].second && arr[i].second == arr[j].first){
                printf("Symmetric pairs are: %d, %d\n", arr[i].first, arr[i].second);
            }
        }
    }   
}

int main() {
    pair list[5] = {{1, 2}, {3, 4}, {2, 1}, {4, 3}, {5, 6}};

    find_symmetric_pairs(list, 5);
    
    return 0;
}