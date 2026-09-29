#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct {
    char key[SIZE];
    int value;
} dict;

dict *combineDict(dict *dict1, int size1, dict *dict2, int size2) {
    dict *result = malloc((size1 + size2) * sizeof(dict));
    int i, j, k = 0;

    for(i = 0; i < size1; i++) {
        strcpy(result[k].key, dict1[i].key);
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        result[k].value = dict1[i].value;
        k++;
    }

    for(i = 0; i < size2; i++) {
        for(j = 0; j < k; j++) {
            if(strcmp(result[j].key, dict2[i].key) == 0) {
                result[j].value += dict2[i].value;
                break;
            }
        }
        if(j == k) {
            strcpy(result[k].key, dict2[i].key);
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[k].value = dict2[i].value;
            k++;
        }
    }

    return result;
}

int main() {
    dict dict1[3] = {{"key1", 1}, {"key2", 2}, {"key3", 3}};
    dict dict2[3] = {{"key1", 4}, {"key4", 5}, {"key5", 6}};

    dict *result = combineDict(dict1, 3, dict2, 3);

    for(int i = 0; i < 5; i++) {
        printf("%s: %d\n", result[i].key, result[i].value);
    }

    free(result);

    return 0;
}