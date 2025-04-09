#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    char value;
    struct Node* left;
    struct Node* right;
};

// Stack structure for storing tree nodes
struct Stack {
    struct Node* array[100];
    int top;
};

// Function to initialize stack
void initStack(struct Stack* stack) {
    stack->top = -1;
}

// Function to push node into stack
void push(struct Stack* stack, struct Node* node) {
    stack->array[++stack->top] = node;
}

// Function to pop node from stack
struct Node* pop(struct Stack* stack) {
    return stack->array[stack->top--];
}

// Function to create a new node
struct Node* newNode(char value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->value = value;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to construct an Expression Tree from postfix expression
struct Node* constructTree(char postfix[]) {
    struct Stack stack;
    initStack(&stack);

    for (int i = 0; postfix[i] != '\0'; i++) {
        struct Node* temp = newNode(postfix[i]);

        // If operand, push to stack
        if (isalnum(postfix[i])) {
            push(&stack, temp);
        }
        // If operator, pop two nodes and make them children
        else if (isOperator(postfix[i])) {
            temp->right = pop(&stack);
            temp->left = pop(&stack);
            push(&stack, temp);
        }
    }

    // Root of the tree
    return pop(&stack);
}

// Inorder traversal (Left, Root, Right)
void inorder(struct Node* root) {
    if (root) {
        inorder(root->left);
        printf("%c ", root->value);
        inorder(root->right);
    }
}

// Preorder traversal (Root, Left, Right)
void preorder(struct Node* root) {
    if (root) {
        printf("%c ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function to evaluate the Expression Tree
int evaluate(struct Node* root) {
    if (!root) return 0;

    // If leaf node (operand), return its value
    if (!root->left && !root->right)
        return root->value - '0'; // Convert char to int

    // Evaluate left and right subtrees
    int left_val = evaluate(root->left);
    int right_val = evaluate(root->right);

    // Apply the operator
    switch (root->value) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': return left_val / right_val;
    }

    return 0;
}

// Main function
int main() {
    char postfix[100]; 
    printf("Enter a postfix expression : ");
    scanf("%s",postfix);

    struct Node* root = constructTree(postfix);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Expression Tree Evaluation: %d\n", evaluate(root));

    return 0;
}

