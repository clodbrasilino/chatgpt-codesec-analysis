#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    void **data;
    int count;
} Dictionary;

bool check_dictionary_empty(Dictionary *dict) {
    if(dict == NULL || dict->data == NULL) {
        return true;
    }
    return dict->count == 0;
}

int main() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
   
    if (dict == NULL) {
        printf("Memory allocation failed for Dictionary\n");
        return 1;
    }

    dict->data = NULL;
    dict->count = 0;
    
    printf("%s\n", check_dictionary_empty(dict) ? "Empty" : "Not Empty");

    dict->data = malloc(sizeof(int) * 10);
    
    if (dict->data == NULL) {
        printf("Memory allocation failed for Dictionary data\n");
        free(dict);
        return 1;
    }

    dict->count = 10;
    printf("%s\n", check_dictionary_empty(dict) ? "Empty" : "Not Empty");

    free(dict->data);
    free(dict);
    
    return 0;
}