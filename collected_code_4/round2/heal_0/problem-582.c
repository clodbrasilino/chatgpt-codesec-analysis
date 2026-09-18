#include <stdbool.h>
#include <stdlib.h>

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
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->data = NULL;
    dict->count = 0;
    printf("%s\n", check_dictionary_empty(dict) ? "Empty" : "Not Empty");

    dict->data = malloc(sizeof(int) * 10);
    dict->count = 10;
    printf("%s\n", check_dictionary_empty(dict) ? "Empty" : "Not Empty");

    free(dict->data);
    free(dict);
    return 0;
}