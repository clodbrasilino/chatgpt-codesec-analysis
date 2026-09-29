#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int length;
} Tuple;

Tuple find_similar(Tuple t1, Tuple t2) {
    int *result = malloc(sizeof(int) * (t1.length < t2.length ? t1.length : t2.length));
    int count = 0;

    for (int i = 0; i < t1.length; i++) {
        for (int j = 0; j < t2.length; j++) {
            if (t1.data[i] == t2.data[j]) {
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                result[count++] = t1.data[i];
                break;
            }
        }
    }

    Tuple t = {result, count};
    return t;
}

int main() {
    Tuple t1 = {(int[]){1, 2, 3, 4, 5}, 5};
    Tuple t2 = {(int[]){4, 5, 6, 7, 8}, 5};

    Tuple t = find_similar(t1, t2);

    for (int i = 0; i < t.length; i++) {
        printf("%d ", t.data[i]);
    }

    free(t.data);

    return 0;
}