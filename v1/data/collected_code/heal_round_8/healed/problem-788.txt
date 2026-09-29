#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Tuple {
    char* str;
    int* list;
    int list_size;
} Tuple;

Tuple* createNewTuple(const char* str, const int* list, int list_size) {
    bool isStrNullTerminated = str[strlen(str)] == '\0';
    if (str == NULL || list == NULL || list_size <= 0 || !isStrNullTerminated) {
        return NULL;
    }

    Tuple* new_tuple = (Tuple*)malloc(sizeof(Tuple));
    if(new_tuple == NULL) return NULL;

    size_t len = strlen(str);
    new_tuple->str = malloc((len + 1) * sizeof(char));
    if(new_tuple->str == NULL) {
        free(new_tuple);
        return NULL;
    }
    snprintf(new_tuple->str, len + 1, "%s", str);

    new_tuple->list_size = list_size;
    new_tuple->list = (int*)malloc(list_size * sizeof(int));
    if(new_tuple->list == NULL) {
        free(new_tuple->str);
        free(new_tuple);
        return NULL;
    }

    memcpy(new_tuple->list, list, list_size * sizeof(int));

    return new_tuple;
}

int main() {
    char* str = "example";
    int list[3] = {1, 2, 3};
    int list_size = sizeof(list) / sizeof(list[0]);
    
    Tuple* my_tuple = createNewTuple(str, list, list_size);
    if(my_tuple == NULL) return 1;

    printf("String: %s\n", my_tuple->str);
    printf("List: ");
    for (int i = 0; i < my_tuple->list_size; i++) {
        printf("%d ", my_tuple->list[i]);
    }
    printf("\n");
    
    free(my_tuple->str);
    free(my_tuple->list);
    free(my_tuple);
    
    return 0;
}