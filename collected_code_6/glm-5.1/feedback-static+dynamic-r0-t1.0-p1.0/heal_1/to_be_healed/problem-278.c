#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as pointer to const [constParameterPointer]
 */
int find_element_count(int *tuple, size_t size, int record) {
    if (tuple == NULL || size == 0) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == record) {
            return (int)i;
        }
    }

    return -1;
}

int main(void) {
    int tuple[] = {10, 20, 30, 40, 50, 60};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    int record = 40;
    
    int count = find_element_count(tuple, size, record);
    
    printf("%d\n", count);
    
    return 0;
}