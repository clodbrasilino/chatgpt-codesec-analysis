int sumEvenNumbers(int l, int r) {
    int sum = 0;
    int start = (l % 2 == 0) ? l : l + 1;
    for (int i = start; i <= r; i += 2) {
        sum += i;
    }
    return sum;
}