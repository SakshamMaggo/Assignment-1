#include <iostream>

using namespace std;

// We have defined a Stack class with the required functions to be used in the problem
class Stack {
    
    int* arr;
    int topIndex;
    int capacity;

    public:
    
        Stack(int size) { // The constructor has been defined for you
            arr = new int[size];
            capacity = size;
            topIndex = -1;
        }

        ~Stack() {
            delete[] arr;
        }

        // Function to add an element to the stack
        void push(int x) {
            if (isFull()) {
                // Stack overflow: cannot push more disks
                cout << "Invalid Input";
                exit(0);
            }
            if (!isEmpty() && x > arr[topIndex]) {
                // Cannot place a larger disk on a smaller one
                cout << "Invalid Input";
                exit(0);
            }
            arr[++topIndex] = x;
        }

        // Function to pop the top element
        int pop() {
            if (isEmpty()) {
                // Stack underflow: no disks to pop
                cout << "Invalid Input";
                exit(0);
            }
            return arr[topIndex--];
        }

        // Function to display the elements of the stack
        void display() const {
            if (isEmpty()) {
                cout << "Empty ";
            } else {
                for (int i = 0; i <= topIndex; i++) {
                    cout << arr[i] << " ";
                }
            }
        }

    private:
        
        // Function to check if the stack is full
        bool isFull() const {
            return topIndex == capacity - 1;
        }

        // Function to check if the stack is empty
        bool isEmpty() const {
            return topIndex == -1;
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
    cout << "\nTower B: ";
    B->display();
    cout << "\nTower C: ";
    C->display();
    cout << "\n";
}

// Recursive function to rearrange disks following Tower of Hanoi rules
void rearrangeDisks(int n, Stack& A, Stack& B, Stack& C, char from, char to, char aux) {
    if(n == 0)
        return;

    // Move n-1 disks from 'from' peg to 'aux' peg using 'to' as auxiliary
    rearrangeDisks(n-1, A, B, C, from, aux, to);

    // Move the nth disk from 'from' peg to 'to' peg
    Stack* sourcePeg;
    Stack* destPeg;

    // Determine the source peg based on the 'from' character
    if(from == 'A') sourcePeg = &A;
    else if(from == 'B') sourcePeg = &B;
    else sourcePeg = &C;

    // Determine the destination peg based on the 'to' character
    if(to == 'A') destPeg = &A;
    else if(to == 'B') destPeg = &B;
    else destPeg = &C;

    // Pop the top disk from the source peg and push it onto the destination peg
    int disk = sourcePeg->pop();
    destPeg->push(disk);

    // Print the move and display the current state of the towers
    cout << "Move disk " << disk << " from " << from << " to " << to << " ";
    displayTowers();

    // Move the n-1 disks from 'aux' peg to 'to' peg using 'from' as auxiliary
    rearrangeDisks(n-1, A, B, C, aux, to, from);
}

int main() { // The main function has been defined for you, do not edit anything here.
    int n;
    cin >> n;

    // Input Validation: Check if the input is a positive integer
    if(n < 1){
        cout << "Invalid Input";
        return 0;
    }

    // Initialize the pegs with the specified number of disks on Peg A
    A = new Stack(n);
    B = new Stack(n);
    C = new Stack(n);

    for(int i = n; i >= 1; i--){
        A->push(i);
    }

    // Display the initial state of the towers
    displayTowers();

    // Solve the Tower of Hanoi problem
    rearrangeDisks(n, *A, *B, *C, 'A', 'C', 'B');

    // Clean up dynamically allocated memory
    delete A;
    delete B;
    delete C;

    return 0;
}
