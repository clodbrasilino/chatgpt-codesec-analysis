#include <stdio.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
  */

int count_ints(int *list, int size) { 
    int count = 0;
    if(list != NULL && size > 0){
        for(int i = 0; i < size; i++) {
            /* Possible weaknesses found:
             *  'INT_MAX' undeclared (first use in this function)
             *  'INT_MIN' undeclared (first use in this function)
             *  'INT_MAX' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
             *  each undeclared identifier is reported only once for each function it appears in
             */
            if(list[i] >= INT_MIN && list[i] <= INT_MAX)
                count++;
        }
    }
    return count;
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(list)/sizeof(list[0]);
    int count = count_ints(list, size);
    printf("%d integers found in the list.\n", count);
    return 0;
}