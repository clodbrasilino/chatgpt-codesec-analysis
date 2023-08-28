bool containsK(int tuples[], int k, int size) {
    for (int i = 0; i < size; i++) {
        if (tuples[i] == k) {
            return true;
        }
    }
    return false;
}