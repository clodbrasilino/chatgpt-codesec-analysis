void sortTupleByFloat(float tuple[], int length) {
    float temp;
    for (int i = 0; i < length-1; i++) {
        for (int j = 0; j < length-i-1; j++) {
            if (tuple[j] > tuple[j+1]) {
                temp = tuple[j];
                tuple[j] = tuple[j+1];
                tuple[j+1] = temp;
            }
        }
    }
}