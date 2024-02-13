
// Q How to pass an array using call by value in C ? Assuming array is declared locally that is inside main() ?
// Ans - While C doesn't technically support passing arrays by value, here's how you can achieve a similar effect by passing a pointer to the array:

#include <stido.h>
#include <conio.h>
 
void modify_array(int arr[], int size); // Accepts a pointer to the first element and the size


void modify_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // Modify the array elements
    }
}


int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    modify_array(arr, size);  // Pass the array's name (which decays to a pointer) and size

    // Print the modified array
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
} 

