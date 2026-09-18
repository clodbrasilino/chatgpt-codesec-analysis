#include <stdbool.h>
#include <stddef.h>

bool isSublist(int *list, size_t listLength, int *sublist, size_t sublistLength) {
    if (!list || !sublist || sublistLength > listLength) {
        return false;
    }

    for (size_t i = 0; i <= (listLength - sublistLength); i++) {
        bool matchFound = true;

        for (size_t j = 0; j < sublistLength; j++) {
            if (list[i+j] != sublist[j]) {
                matchFound = false;
                break;
            }
        }

        if (matchFound) {
            return true;
        }
    }

    return false;
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sublist[] = {3, 4, 5};

    if (isSublist(list, sizeof(list) / sizeof(list[0]), sublist, sizeof(sublist) / sizeof(sublist[0]))) {
        /* Possible weaknesses found:
         *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
         *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        printf("Sublist is in the list\n");
    } else {
        printf("Sublist is not in the list\n");
    }

    return 0;
}