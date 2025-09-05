#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* rear = NULL;

// Enqueue
void enqueue(int value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = value;
    if (rear == NULL) {
        rear = temp;
        rear->next = rear;  // circular
    } else {
        temp->next = rear->next;
        rear->next = temp;
        rear = temp;
    }
    printf("Inserted %d\n", value);
}

// Dequeue
int dequeue() {
    if (rear == NULL) {
        printf("Queue Underflow\n");
        return -1;
    }
    struct Node* front = rear->next;
    int value = front->data;
    if (rear == front) { // only one node
        rear = NULL;
    } else {
        rear->next = front->next;
    }
    free(front);
    return value;
}

// Display
void display() {
    if (rear == NULL) {
        printf("Queue is Empty\n");
        return;
    }
    struct Node* temp = rear->next;
    printf("Queue: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != rear->next);
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    printf("Deleted %d\n", dequeue());
    display();
    enqueue(40);
    enqueue(50);
    display();
    return 0;
}
