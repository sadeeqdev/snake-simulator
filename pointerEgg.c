#include <stdio.h>

int main()
{
    int tre;  // Declare an integer variable
    int *ptr; // Declare an integer pointer

    ptr = &tre; // Assign the address of 'tre' to the pointer

    *ptr = 50; // Assign the value 50 to the variable 'tre' through the pointer

    // Access the value stored by the pointer
    printf("Value stored in 'tre': %d\n", tre);

    return 0;
}
