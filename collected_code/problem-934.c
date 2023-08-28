/* Function to find the nth Delannoy number */
unsigned long long int delannoy(int m, int n) {
    // Base case
    if (m == 0 || n == 0) {
        return 1;
    }
    // Recursive case
    return delannoy(m - 1, n) +
           delannoy(m - 1, n - 1) +
           delannoy(m, n - 1);
}