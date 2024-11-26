#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 50

char opStack[SIZE];   // Stack for operators
int numStack[SIZE]; // Stack for numbers
int topOp = -1, topNum = -1;

void pushOp(char opr) {
    opStack[++topOp] = opr;
}

char popOp() {
    return opStack[topOp--];
}

void pushNum(int num) {
    numStack[++topNum] = num;
}

int popNum() {
    return numStack[topNum--];
}

int precedence(char opr) {  //to check the precedence of a an operator
    switch (opr) {
        case '+': 
        case '-': return 1;
        case '*': 
        case '/': return 2;
    }
}

int evaluate(int a, int b, char opr) {  //to perform arithemetic operation on 2 numbers
    switch (opr) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Error: Division by zero.\n");
                exit(1);
            }
            return a / b;
    }
    return 0;
}

void evaluateExpression() { //to perform arithemetic operation on the remaining numbers in the stack
    while (topOp != -1) {
        int b = popNum();
        int a = popNum();
        char opr = popOp();
        pushNum(evaluate(a, b, opr));
    }
}

void processExpression(char* input) {
    int i = 0;
    while (input[i] != '\0') {
        if (input[i] == ' ') {
            i++; // ignore whitespace
            continue;
        } 
        else if (isdigit(input[i])) {
            int num = 0;
            while (isdigit(input[i])) { // multi-digit numbers
                num = num * 10 + (input[i] - '0');
                i++;
            }
            pushNum(num);
            continue;
        } 
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' ) {
            while (topOp != -1 && precedence(opStack[topOp]) >= precedence(input[i])) { //compare the precedence of the previous operator and the current operator
                int b = popNum();
                int a = popNum();
                char opr = popOp();
                pushNum(evaluate(a, b, opr));
            }
            pushOp(input[i]);
        } 
        else {
            printf("Error: Invalid expression.\n");
            exit(1);
        }
        i++;
    }
    evaluateExpression(); 
}

int main() {
    char input[SIZE];
    printf("Enter a mathematical expression: ");
    fgets(input, SIZE, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character

    processExpression(input);

    if (topNum == 0) { // The result should be the only number in the stack
        printf("Result: %d\n", popNum());
    } else {
        printf("Error: Invalid expression.\n");
    }
    return 0;
}
