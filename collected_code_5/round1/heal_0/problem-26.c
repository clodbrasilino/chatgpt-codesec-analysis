#include <stdio.h>
#include <stdbool.h>

bool is_k_elements(int tuple_list[], int size, int k){
    if (size != k){
        return false;
    }
    for(int i = 0; i < size; i++){
        if(tuple_list[i] == 0){
            return false;
        }
    }
    return true;
}

int main(){
    int tuple_list[4] = {1, 2, 3, 4};
    int size = sizeof(tuple_list)/sizeof(tuple_list[0]);
    int k = 4;
    
    if(is_k_elements(tuple_list, size, k)){
        printf("The given tuple list has all k elements\n");
    }else{
        printf("The given tuple list does not have all k elements\n");
    }

    return 0;
}