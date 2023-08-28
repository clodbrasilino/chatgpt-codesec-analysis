typedef struct {
    int *elements;
    int size;
} Tuple;

void extractMinMaxKElements(Tuple tuple, int k, int* minimum, int* maximum) {
    *minimum = tuple.elements[0];
    *maximum = tuple.elements[0];

    for (int i = 1; i < tuple.size; i++) {
        if (tuple.elements[i] < *minimum) {
            *minimum = tuple.elements[i];
        }
        if (tuple.elements[i] > *maximum) {
            *maximum = tuple.elements[i];
        }
    }
}