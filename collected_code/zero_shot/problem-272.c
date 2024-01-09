#include<stdio.h>

// Define a tuple structure
typedef struct {
   int a;
   int b;
} Tuple;

// Function to extract the rear element from list of tuples records
void extractRearElement(Tuple arr[], int n) {
   // Print the rear element of each tuple
   for (int i = 0; i < n; i++) {
      printf("%d\n", arr[i].b);
   }
}

int main() {
   // Create an array of tuples
   Tuple records[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
   int n = sizeof(records) / sizeof(records[0]);

   // Call the function to extract rear element
   extractRearElement(records, n);

   return 0;
}