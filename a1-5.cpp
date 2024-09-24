#include <iostream>

using namespace std;

// We have defined a Stack class with the required functions to be used in the problem
class Stack {
    
    int* arr;
    int top;
    int capacity;

    public:
    
        Stack(int size) { // The constructor has been defined for you
            arr = new int[size];
            capacity = size;
            top = -1;
        }

        ~Stack() {
            delete[] arr;
        }

        // Function to add an element to the stack
        void push(int x) {
            if (isFull()) {
                // Cannot push onto a full stack
                cout << "Invalid Input";
                exit(0);
            }
            arr[++top] = x;
        }

        // Function to pop the top element
        int pop() {
            if (isEmpty()) {
                // Cannot pop from an empty stack
                cout << "Invalid Input";
                exit(0);
            }
            return arr[top--];
        }

        // Function to display the elements of the stack
        void display() const {
            if (isEmpty()) {
                cout << "Empty";
            } else {
                for (int i = 0; i <= top; i++) {
                    cout << arr[i] << " ";
                }
            }
            cout << endl;
        }

    private:
    
        // Function to check if the stack is full
        bool isFull() const {
            return top == capacity - 1;
        }

        // Function to check if the stack is empty
        bool isEmpty() const {
            return top == -1;
        }

};

// Stacks have been defined globally for the towers A, B, and C for printing the towers at each step
Stack* A;
Stack* B;
Stack* C;

// Function to display the contents of the towers
void displayTowers() {
    cout << "Tower A: ";
    A->display();
    cout << "Tower B: ";
    B->display();
    cout << "Tower C: ";
    C->display();
    cout << "\n";
}

// Recursive function to rearrange disks following Tower of Hanoi rules
void rearrangeDisks(int n, Stack& source, Stack& destination, Stack& auxiliary, char from, char to, char aux) {
    if (n == 0)
        return;

    // Move n-1 disks from source to auxiliary
    rearrangeDisks(n - 1, source, auxiliary, destination, from, aux, to);

    // Move the nth disk from source to destination
    int disk = source.pop();
    destination.push(disk);

    // Print the move and display the current state of the towers
    cout << "Move disk " << disk << " from " << from << " to " << to << endl;
    displayTowers();

    // Move the n-1 disks from auxiliary to destination
    rearrangeDisks(n - 1, auxiliary, destination, source, aux, to, from);
}

int main() { // The main function has been defined for you, do not edit anything here.
    int n;
    cin >> n;

    // Input Validation: Check if the input is a positive integer
    if (n < 0) {
        cout << "Invalid Input";
        return 0;
    }

    A = new Stack(n);
    B = new Stack(n);
    C = new Stack(n);

    for (int i = n; i >= 1; i--) {
        A->push(i);
    }

    displayTowers();

    rearrangeDisks(n, *A, *C, *B, 'A', 'C', 'B');

    delete A;
    delete B;
    delete C;

    return 0;
}
