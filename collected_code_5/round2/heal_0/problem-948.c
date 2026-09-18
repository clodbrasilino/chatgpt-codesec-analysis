#include <stdio.h>

typedef struct{
    int a, b, c;
} Tuple;

int getItem(Tuple* t, int index){
    if(t == NULL)
        return -1;

    switch(index){
        case 0: return t->a;
        case 1: return t->b;
        case 2: return t->c;
        default: return -1;
    }
}

int main(){
    Tuple t = {1, 2, 3};
    
    printf("%d\n", getItem(&t, 0)); // 1
    printf("%d\n", getItem(&t, 1)); // 2
    printf("%d\n", getItem(&t, 2)); // 3

    return 0;
}