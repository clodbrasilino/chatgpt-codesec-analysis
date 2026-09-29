#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int value;
} Dictionary;

Dictionary *create_dict(int size) {
    Dictionary *dict = (Dictionary*)malloc(size * sizeof(Dictionary));
    if(dict == NULL){
        printf("Error! memory not allocated.");
        exit(0);
    }
    return dict;
}

int get_by_index(Dictionary *dict, int size, int index){
    if(index < 0 || index >= size){
        printf("Error! Index out of bounds.");
        exit(0);
    }
    return dict[index].value;
}

void free_dict(Dictionary *dict){
    free(dict);
}

int main(){
    int size = 2;
    Dictionary *dict = create_dict(size);
    dict[0].key = 1;
    dict[0].value = 10;
    dict[1].key = 2;
    dict[1].value = 20;
    printf("Value: %d\n", get_by_index(dict, size, 0));
    free_dict(dict);
    return 0;
}