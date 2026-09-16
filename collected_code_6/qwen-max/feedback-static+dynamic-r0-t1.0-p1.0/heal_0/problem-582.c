#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int count;
} Dictionary;

bool isDictionaryEmpty(Dictionary *dict) {
    if (dict == NULL) {
        return false;
    }
    return dict->count == 0;
}

int main() {
    Dictionary *myDict = (Dictionary *)malloc(sizeof(Dictionary));
    if (myDict == NULL) {
        return EXIT_FAILURE;
    }
    myDict->count = 0;

    bool empty = isDictionaryEmpty(myDict);
    if (empty) {
        // Handle empty dictionary
    }

    free(myDict);
    return EXIT_SUCCESS;
}