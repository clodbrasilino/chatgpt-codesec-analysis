#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

typedef struct {
    int size;
} Dictionary;

/* Possible weaknesses found:
 *  Parameter 'dict' can be declared as pointer to const [constParameterPointer]
 */
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
        /* Possible weaknesses found:
         *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
         *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("Dictionary is empty.\n");
    } else {
        printf("Dictionary is not empty.\n");
    }

    free(myDict);
    return 0;
}