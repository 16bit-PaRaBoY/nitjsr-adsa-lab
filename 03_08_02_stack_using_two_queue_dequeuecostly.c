#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
    int arr[SIZE];
    int front, rear;
} Queue;

void init(Queue* q) { q->front = q->rear = -1; }
int isEmpty(Queue* q) { return q->front == -1; }
int isFull(Queue* q) { return (q->rear + 1) % SIZE == q->front; }

void enqueue(Queue* q, int x) {
    if (isFull(q)) return;
    if (isEmpty(q)) q->front = 0;
    q->rear = (q->rear + 1) % SIZE;
    q->arr[q->rear] = x;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    int val = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front = (q->front + 1) % SIZE;
    return val;
}

// ---------- Stack using two queues ----------
Queue q1, q2;

void push(int x) {
    enqueue(&q1, x);
    printf("Pushed %d\n", x);
}

int pop() {
    if (isEmpty(&q1)) {
        printf("Stack Underflow\n");
        return -1;
    }

    // Move all except last to q2
    while (q1.front != q1.rear)
        enqueue(&q2, dequeue(&q1));

    // Last element in q1 = stack top
    int val = dequeue(&q1);

    // Swap q1 and q2
    Queue temp = q1;
    q1 = q2;
    q2 = temp;

    return val;
}

int main() {
    init(&q1); init(&q2);

    push(10);
    push(20);
    push(30);

    printf("Popped %d\n", pop());
    printf("Popped %d\n", pop());

    push(40);
    printf("Popped %d\n", pop());
    return 0;
}
