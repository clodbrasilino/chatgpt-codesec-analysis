#include <stdio.h>
#include <stdbool.h>

bool checkEvenIndexEvenNumbers(int* list, int size) {
    for (int i = 0; i < size; i += 2){
        if ((list[i] % 2) != 0 ) {
            return false;
        }
    }
    return true;
}

int main() {
    int list1[5] = {2, 1, 4, 3, 6};
    int list2[5] = {2, 3, 7, 1, 2};
  
    bool result1 = checkEvenIndexEvenNumbers(list1, 5);
    bool result2 = checkEvenIndexEvenNumbers(list2, 5);

    printf("%s\n", result1 ? "True" : "False");
    printf("%s\n", result2 ? "True" : "False");

    return 0;
}