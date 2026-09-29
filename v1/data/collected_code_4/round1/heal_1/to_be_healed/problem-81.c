#include <stdio.h>

struct Tuple {
    int x;
    int y;
};

/* Possible weaknesses found:
 *  declared here
 */
struct Tuple ZipTuples(struct Tuple a, struct Tuple b) {

    struct Tuple result;
    if(&a == NULL || &b == NULL) {
        printf("Input tuples are invalid");
        /* Possible weaknesses found:
         *  'return' with no value, in function returning non-void
         */
        return;
    }
    
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

int main() {

    struct Tuple tuple1 = {1, 2};
    struct Tuple tuple2 = {3, 4};

    struct Tuple zipped = ZipTuples(tuple1, tuple2);

    printf("Zipped tuple: %d, %d\n", zipped.x, zipped.y); 
    return 0;
}