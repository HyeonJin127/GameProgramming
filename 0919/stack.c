#include <stdio.h>

#define MAX_SIZE 100 
 
typedef struct {
    int data[MAX_SIZE]; 
    int top; 
} Stack;
 
void initialize(Stack *s) {
    s->top = -1; 
}
 
int isEmpty(Stack *s) {
    return s->top == -1; 
}
 
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1; 
}
 
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Error: Stack is full!\n");
        return;
    }
    s->top++;
    s->data[s->top] = value;
    printf("%d pushed to stack\n", value);
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Error: Stack is empty!\n");
        return -1;
    }
    int poppedValue = s->data[s->top];
    s->top--;
    return poppedValue;
}

int main() {
    Stack s;
    initialize(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30); 

    printf("Popped item: %d\n", pop(&s));
    printf("Popped item: %d\n", pop(&s));
    printf("Popped item: %d\n", pop(&s));
    printf("Popped item: %d\n", pop(&s));

    return 0;
}

