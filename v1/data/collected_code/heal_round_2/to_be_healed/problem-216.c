#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool isSubset(const int *list1, int n1, const int *list2, int n2) {
    if (n1 == 0) {
        return true;
    }
    if (n2 == 0) {
        return false;
    }
    if (list1[0] == list2[0]) {
        return isSubset(list1 + 1, n1 - 1, list2 + 1, n2 - 1);
    }
    return isSubset(list1, n1, list2 + 1, n2 - 1);
}

int main(){
    int list1[5] = {1, 2, 3, 4, 5};
    int list2[6] = {0, 1, 2, 3, 4, 5};
    int n1 = sizeof(list1)/sizeof(list1[0]);
    int n2 = sizeof(list2)/sizeof(list2[0]);
    
    if(isSubset(list1, n1, list2, n2))
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("List1 is a subset of List2\n");
    else
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("List1 is not a subset of List2\n");
    
    return 0;
}