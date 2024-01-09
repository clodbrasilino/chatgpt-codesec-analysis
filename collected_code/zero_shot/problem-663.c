int findLargestK(int x, int y) {
    int k = x - 1;
    while (k % x != y && k > 0) {
        k--;
    }
    return k;
}