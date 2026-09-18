#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

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
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dict' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dict->data = NULL;
    dict->count = 0;
    /* Possible weaknesses found:
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     */
    printf("%s\n", check_dictionary_empty(dict) ? "Empty" : "Not Empty");

    dict->data = malloc(sizeof(int) * 10);
    dict->count = 10;
    printf("%s\n", check_dictionary_empty(dict) ? "Empty" : "Not Empty");

    free(dict->data);
    free(dict);
    return 0;
}