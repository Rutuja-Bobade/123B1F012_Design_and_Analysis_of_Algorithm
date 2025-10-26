#include <stdio.h>

// 1. With arguments, without return
void add_With_Args_No_Return(int a, int b, int c) {
    int sum = a + b + c;
    printf("Sum (with arguments, no return): %d\n", sum);
}

// 2. With arguments, with return
int add_With_Args_Return(int a, int b, int c) {
    return a + b + c;
}

// 3. Without arguments, without return
void add_No_Args_No_Return() {
    int a = 5, b = 10, c = 15;
    int sum = a + b + c;
    printf("Sum (no arguments, no return) , (a= 5, b=10, c=15): %d\n", sum);
}

// 4. Without arguments, with return
int add_No_Args_With_Return() {
    int a = 5, b = 10, c = 15;
    return a + b + c;
}

int main() {
    int x, y, z;
    printf("Enter three numbers: ");
    scanf("%d %d %d", &x, &y, &z);

    add_With_Args_No_Return(x, y, z);

    int result1 = add_With_Args_Return(x, y, z);
    printf("Sum (with arguments, with return): %d\n", result1);

    add_No_Args_No_Return();

    int result2 = add_No_Args_With_Return();
    printf("Sum (no arguments, with return) , (a= 5, b=10, c=15): %d\n", result2);

    return 0;
}
