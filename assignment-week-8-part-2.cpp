#include <iostream>
#include <chrono> // For measuring execution time

// Node structure representing each person.
struct Node
{
    int personNumber;
    Node *next;

    Node(int num) : personNumber(num), next(nullptr) {}
};

// Function to simulate the Josephus problem using a circular linked list.
int josephus(int N, int M)
{
    // Create circular linked list for N people.
    Node *head = new Node(1);
    Node *prev = head;

    // Create the circle.
    for (int i = 2; i <= N; ++i)
    {
        Node *newNode = new Node(i);
        prev->next = newNode;
        prev = newNode;
    }
    prev->next = head; // Complete the circle.

    Node *current = head;

    // Eliminate every M-th person.
    while (current->next != current)
    { // Loop until only one person remains.
        // Find the M-th node to eliminate.
        for (int i = 1; i < M; ++i)
        {
            current = current->next;
        }

        // Eliminate the M-th person (person after current).
        Node *toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
        current = current->next; // Move to the next person holding the ball.
    }

    // The last remaining person is the winner.
    int winner = current->personNumber;
    delete current; // Clean up the last node.

    return winner;
}

int main()
{
    // Case 1: N = 5 and M = 1, 2, 3
    int N1 = 5;
    int M1_1 = 1, M1_2 = 2, M1_3 = 3;

    std::cout << "For N = 5, M = 1, the winner is: " << josephus(N1, M1_1) << "\n";
    std::cout << "For N = 5, M = 2, the winner is: " << josephus(N1, M1_2) << "\n";
    std::cout << "For N = 5, M = 3, the winner is: " << josephus(N1, M1_3) << "\n";

    // Case 2: N = 10000 and M = 1
    int N2 = 10000;
    int M2 = 1;

    // Measure execution time using chrono
    auto start = std::chrono::high_resolution_clock::now();
    int winner = josephus(N2, M2);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "For N = 10000, M = 1, the winner is: " << winner << "\n";
    std::cout << "Execution time: " << elapsed.count() << " seconds.\n";

    return 0;
}