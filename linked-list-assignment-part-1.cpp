#include <iostream>

using namespace std;

// Node structure for the singly linked list
struct Node
{
    int data;
    Node *next;
};

// Function to create a new node
Node *createNode(int data)
{
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Function to insert a node at the end of the list
void insertAtEnd(Node *&head, int data)
{
    Node *newNode = createNode(data);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to display the list
void displayList(Node *head)
{
    if (head == nullptr)
    {
        cout << "The list is empty." << endl;
        return;
    }
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

// Function to delete a node at the beginning of the list
void deleteAtBeginning(Node *&head)
{
    if (head == nullptr)
    {
        cout << "List is empty, nothing to delete." << endl;
        return;
    }
    Node *temp = head;
    head = head->next;
    cout << "Deleted node with value: " << temp->data << " from the beginning." << endl;
    delete temp;
}

// Function to delete a node at the end of the list
void deleteAtEnd(Node *&head)
{
    if (head == nullptr)
    {
        cout << "List is empty, nothing to delete." << endl;
        return;
    }

    if (head->next == nullptr)
    {
        // Only one node in the list
        cout << "Deleted node with value: " << head->data << " from the end." << endl;
        delete head;
        head = nullptr;
    }
    else
    {
        Node *temp = head;
        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }
        Node *lastNode = temp->next;
        temp->next = nullptr;
        cout << "Deleted node with value: " << lastNode->data << " from the end." << endl;
        delete lastNode;
    }
}

// Function to delete a node after a given node
void deleteAfterNode(Node *prevNode)
{
    if (prevNode == nullptr || prevNode->next == nullptr)
    {
        cout << "The given node is invalid or there is no node to delete after it." << endl;
        return;
    }

    Node *temp = prevNode->next;
    prevNode->next = temp->next;
    cout << "Deleted node with value: " << temp->data << " after the node with value " << prevNode->data << "." << endl;
    delete temp;
}

// Main function
int main()
{
    Node *head = nullptr;

    // Insert some nodes into the list
    insertAtEnd(head, 10);
    insertAtEnd(head, 20);
    insertAtEnd(head, 30);
    insertAtEnd(head, 40);
    insertAtEnd(head, 50);

    // Display the initial list
    cout << "Initial List:" << endl;
    displayList(head);

    // Deleting node at the beginning
    deleteAtBeginning(head);
    cout << "List after deleting at the beginning:" << endl;
    displayList(head);

    // Deleting node at the end
    deleteAtEnd(head);
    cout << "List after deleting at the end:" << endl;
    displayList(head);

    // Deleting node after the first node (now 20)
    deleteAfterNode(head);
    cout << "List after deleting after the first node:" << endl;
    displayList(head);

    return 0;
}