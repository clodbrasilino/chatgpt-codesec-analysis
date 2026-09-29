#include <stdio.h>

/* Possible weaknesses found:
 *  declared here
 */
int count_lists(int tuple[]) {
    int count = 0;
    /* Possible weaknesses found:
     *  'sizeof' on array function parameter 'tuple' will return size of 'int *' [-Wsizeof-array-argument]
     */
    for (int i = 0; i < sizeof(tuple); i++) {
        /* Possible weaknesses found:
         *  expected expression before 'typeof'
         */
        if (typeof(tuple[i]) == list) {
            count++;
        }
    }
    return count;
}

int main() {
    /* Possible weaknesses found:
     *  expected expression before ',' token
     *  expected ']' before ',' token
     */
    int tuple[] = {1, 2, 3, [4, 5], [6, 7]};
    int num_lists = count_lists(tuple);
    printf("%d", num_lists);
    return 0;
}