#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple *list;
    int size;
} List;

int identicalList(List list1, List list2){
    if(list1.size != list2.size)
        return 0;

    for(int i=0; i<list1.size; i++) {
        if(list1.list[i].x != list2.list[i].x || list1.list[i].y != list2.list[i].y)
            return 0;
    }

    return 1;
}

int main(){
    List list1, list2;
    
    list1.size = 3;
    list1.list = (Tuple *)malloc(sizeof(Tuple)*list1.size);
    if(list1.list == NULL)
        return 1;

    list1.list[0].x = 1; list1.list[0].y = 2;
    list1.list[1].x = 3; list1.list[1].y = 4;
    list1.list[2].x = 5; list1.list[2].y = 6;

    list2.size = 3;
    list2.list = (Tuple *)malloc(sizeof(Tuple)*list2.size);
    if(list2.list == NULL){
        free(list1.list);
        return 1;
    }
    
    list2.list[0].x = 1; list2.list[0].y = 2;
    list2.list[1].x = 3; list2.list[1].y = 4;
    list2.list[2].x = 5; list2.list[2].y = 6;

    if(identicalList(list1, list2))
        printf("Lists are identical\n");
    else
        printf("Lists are not identical\n");

    free(list1.list);
    free(list2.list);

    return 0;
}
