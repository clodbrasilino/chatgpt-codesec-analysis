#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
bool are_elements_unique(int *list, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (list[i] == list[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int list[] = {5, 3, 7, 9, 5};
    int size = sizeof(list) / sizeof(list[0]);
    bool result = are_elements_unique(list, size);
    
    if (result) {
        printf("All elements are unique.\n");
    } else {
        printf("There are duplicate elements.\n");
    }
    
    return 0;
}