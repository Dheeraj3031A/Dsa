#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char x) {
    stack[++top] = x;
}

char pop() {
    if (top == -1)
        return '\0';
    else
        return stack[top--];
}

int precedence(char x) {
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    if (x == '^')
        return 3;
    return 0;
}

int main() {
    char infix[MAX], postfix[MAX];
    int i, k = 0;

    printf("Enter Infix Expression: ");
    scanf("%99s", infix);

    for (i = 0; infix[i] != '\0'; i++) {

        if (isalnum((unsigned char)infix[i])) {
            postfix[k++] = infix[i];
        }

        else if (infix[i] == '(') {
            push(infix[i]);
        }

        else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = pop();

            if (top == -1) {
                printf("Invalid Expression\n");
                return 1;
            }

            pop();
        }

        else {
            while (top != -1 && stack[top] != '(' &&
                   (precedence(stack[top]) > precedence(infix[i]) ||
                   (precedence(stack[top]) == precedence(infix[i])
                   && infix[i] != '^'))) {
                postfix[k++] = pop();
            }

            push(infix[i]);
        }
    }

    while (top != -1) {
        if (stack[top] == '(') {
            printf("Invalid Expression\n");
            return 1;
        }

        postfix[k++] = pop();
    }

    postfix[k] = '\0';

    printf("Postfix Expression: %s\n", postfix);

    return 0;
}
