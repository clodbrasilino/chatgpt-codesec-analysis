#include <stdbool.h>
 /* Possible weaknesses found:
  *  'NULL' is defined in header '<stddef.h>'; did you forget to '#include <stddef.h>'?
  */

bool checkSameElements(const int* arr, int size) {

    /* Possible weaknesses found:
     *  'NULL' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (size == 0 || arr == NULL) {
        return false;
    }
    
    int firstElement = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] != firstElement) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 1, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    bool result = checkSameElements(arr, size);

    return 0;
}