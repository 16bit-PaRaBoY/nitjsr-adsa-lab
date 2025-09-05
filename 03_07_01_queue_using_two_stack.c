#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
    int arr[SIZE];
    int top;
} Stack;

void init(Stack* s) { s->top = -1; }
int isEmpty(Stack* s) { return s->top == -1; }
void push(Stack* s, int x) { s->arr[++s->top] = x; }
int pop(Stack* s) { return s->arr[s->top--]; }
int peek(Stack* s) { return s->arr[s->top]; }

// Queue using two stacks
Stack s1, s2;

void enqueue(int x) {
    // Move all from s1 to s2
    while (!isEmpty(&s1))
        push(&s2, pop(&s1));

    // Push new element into s1
    push(&s1, x);

    // Move back all from s2 to s1
    while (!isEmpty(&s2))
        push(&s1, pop(&s2));

    printf("Enqueued %d\n", x);
}

int dequeue() {
    if (isEmpty(&s1)) {
        printf("Queue Underflow\n");
        return -1;
    }
    return pop(&s1);
}

int main() {
    init(&s1);
    init(&s2);

    enqueue(10);
    enqueue(20);
    enqueue(30);

    printf("Dequeued %d\n", dequeue());
    printf("Dequeued %d\n", dequeue());

    enqueue(40);
    printf("Dequeued %d\n", dequeue());
    return 0;
}
