bool isIncreasing(int numbers[], int length) {
    for (int i = 1; i < length; i++) {
        if (numbers[i] <= numbers[i - 1]) {
            return false;
        }
    }
    return true;
}