#include <stdbool.h>
#include <stddef.h>

bool checkArrPattern(const int arr[], const int size, const int patterns[], const int patternSize) {
    if(arr == NULL || patterns == NULL || size < 1 || patternSize < 1)
        return false;
    
    int patternIndex = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == patterns[patternIndex]) {
            patternIndex++;
        }
        if (patternIndex == patternSize) {
            return true;
        }
    }
    return false;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int patterns[] = {2, 3, 4};

    bool result = checkArrPattern(arr, 5, patterns, 3);

    return 0;
}