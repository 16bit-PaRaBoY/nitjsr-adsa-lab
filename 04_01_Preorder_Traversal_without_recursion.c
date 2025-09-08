#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Create a new node
Node* newNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = val;
    n->left = n->right = NULL;
    return n;
}

// Stack for iterative traversal
typedef struct {
    Node* arr[100];
    int top;
} Stack;

void push(Stack* s, Node* n) { s->arr[++s->top] = n; }
Node* pop(Stack* s) { return s->arr[s->top--]; }
int isEmpty(Stack* s) { return s->top == -1; }

// Preorder traversal without recursion
void preorder(Node* root) {
    if (!root) return;
    Stack s; s.top = -1;
    push(&s, root);
    while (!isEmpty(&s)) {
        Node* cur = pop(&s);
        printf("%d ", cur->data);
        if (cur->right) push(&s, cur->right);
        if (cur->left) push(&s, cur->left);
    }
}

// Build tree using user input (-1 for NULL)
Node* createTree() {
    int val;
    printf("Enter node value (-1 for NULL): ");
    scanf("%d", &val);
    if (val == -1) return NULL;

    Node* root = newNode(val);

    printf("Enter left child of %d\n", val);
    root->left = createTree();

    printf("Enter right child of %d\n", val);
    root->right = createTree();

    return root;
}

int main() {
    printf("Create your binary tree:\n");
    Node* root = createTree();

    printf("\nPreorder Traversal: ");
    preorder(root);
    printf("\n");
    return 0;
}
