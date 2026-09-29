#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int size;
} Dictionary;

bool isDictionaryEmpty(Dictionary *dict) {
    if (dict == NULL) {
        return true;
    }
    return dict->size == 0;
}

int main() {
    Dictionary *myDict = (Dictionary *)malloc(sizeof(Dictionary));
    myDict->size = 0;

    if (isDictionaryEmpty(myDict)) {
        printf("Dictionary is empty.\n");
    } else {
        printf("Dictionary is not empty.\n");
    }

    free(myDict);
    return 0;
}