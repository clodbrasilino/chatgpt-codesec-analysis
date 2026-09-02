#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as pointer to const [constParameterPointer]
 */
int count_occurrences(int *tuple, size_t length, int element) {
    int count = 0;
    for (size_t i = 0; i < length; ++i) {
        if (tuple[i] == element) {
            count++;
        }
    }
    return count;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5, 2, 2, 6, 7, 2};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    int element = 2;

    int occurrences = count_occurrences(tuple, length, element);
    printf("Element %d occurs %d times in the tuple.\n", element, occurrences);

    return 0;
}