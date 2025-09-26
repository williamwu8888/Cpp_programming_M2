#include <stdio.h>

int main() {
    char name[50];  // Variable to store the user's name

    printf("Enter your name: ");
    scanf("%49s", name);  // Read the name from input

    printf("Hello, %s! Welcome to C programming.\n", name);

    return 0;
}


