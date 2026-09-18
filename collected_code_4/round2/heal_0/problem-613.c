#include <stdio.h>
#include <limits.h>

typedef struct {
    int record;
} Tuple;

int find_max_value(Tuple* arr,size_t len){
    int max_val = INT_MIN;

    for(size_t i = 0; i < len; i++){
        int current_record = arr[i].record;
        if(current_record > max_val){
            max_val = current_record;
        }
    }

    return max_val;
}

int main(){
    Tuple tuples[] = {{5}, {10}, {15}, {2}, {0}, {-7}, {8}, {3}, {-5}};
    size_t len = sizeof(tuples) / sizeof(Tuple);
    int max_val = find_max_value(tuples, len);
    printf("Max Value: %d\n", max_val);

    return 0;
}