#include <stdio.h>
#include <stdlib.h>

typedef struct Dictionary {
    struct Dictionary *nestedDict;
} Dictionary;

int findDepth(Dictionary *dict) {
    if (dict == NULL) {
        return 0;
    }
    return 1 + findDepth(dict->nestedDict);
}

int main() {
    Dictionary *dict1 = (Dictionary*)malloc(sizeof(Dictionary));
    Dictionary *dict2 = (Dictionary*)malloc(sizeof(Dictionary));
    Dictionary *dict3 = (Dictionary*)malloc(sizeof(Dictionary));
    dict1->nestedDict = dict2;
    dict2->nestedDict = dict3;
    dict3->nestedDict = NULL;

    printf("Depth of dictionary: %d\n", findDepth(dict1));

    free(dict1);
    free(dict2);
    free(dict3);

    return 0;
}