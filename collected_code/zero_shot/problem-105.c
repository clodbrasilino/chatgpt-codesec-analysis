int countTrueBooleans(bool list[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i]) {
            count++;
        }
    }
    return count;
}