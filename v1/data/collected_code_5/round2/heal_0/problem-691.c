#include <stdio.h>
#include <stdlib.h>

struct tuple{
    int first;
    int second;
};

struct tuple* GroupBySecondElement(struct tuple* list, int size) {

    struct tuple* newList = (struct tuple*)malloc(size * sizeof(struct tuple));

    if(!newList) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(list[i].second == list[j].second) {
                newList[i].first = list[j].first;
                newList[i].second = list[j].second;
                break;
            }
        }
    }

    return newList;
}

int main() {

    int size = 5;
    struct tuple list[5] = { {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10} };

    struct tuple* newList = GroupBySecondElement(list, size);
    
    if(newList != NULL) {
      for(int i = 0; i < size; ++i)
          printf("Tuple %d: First Item = %d, Second Item = %d\n", i, newList[i].first, newList[i].second);

      free(newList);
    }

    return 0;
}