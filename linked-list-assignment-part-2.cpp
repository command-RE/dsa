#include <iostream>
#include <string>

using namespace std;

// Structure to store file information
struct File
{
    string name;
    int size;             // File size in bytes
    int modificationTime; // Modification time (simulated as an integer)
};

// Node structure for the linked list
struct Node
{
    File file;
    Node *next;
};

// Function to create a new node
Node *createNode(const string &name, int size, int modificationTime)
{
    Node *newNode = new Node();
    newNode->file.name = name;
    newNode->file.size = size;
    newNode->file.modificationTime = modificationTime;
    newNode->next = nullptr;
    return newNode;
}

// Function to insert a file into the linked list (sorted by size)
void insertFileSorted(Node *&head, const string &name, int size, int modificationTime)
{
    Node *newNode = createNode(name, size, modificationTime);

    // If the list is empty or the new file is smaller than the head, insert at the beginning
    if (head == nullptr || head->file.size > size)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        // Find the correct position in the list to insert the new file
        Node *current = head;
        while (current->next != nullptr && current->next->file.size <= size)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to display the list of files
void displayFiles(Node *head)
{
    if (head == nullptr)
    {
        cout << "No files in the folder." << endl;
        return;
    }

    cout << "Files in the folder (sorted by size):" << endl;
    Node *current = head;
    while (current != nullptr)
    {
        cout << "Name: " << current->file.name
             << ", Size: " << current->file.size
             << ", Modification Time: " << current->file.modificationTime << endl;
        current = current->next;
    }
}

// Function to delete all files with the smallest size
void deleteSmallestFiles(Node *&head)
{
    if (head == nullptr)
    {
        cout << "No files to delete." << endl;
        return;
    }

    // Find the smallest size in the list
    int smallestSize = head->file.size;

    // Delete all files with the smallest size
    while (head != nullptr && head->file.size == smallestSize)
    {
        Node *temp = head;
        head = head->next;
        cout << "Deleted file: " << temp->file.name << " with size " << temp->file.size << endl;
        delete temp;
    }
}

// Main function
int main()
{
    Node *folder = nullptr;

    // Insert some files into the folder
    insertFileSorted(folder, "file1.txt", 500, 1620); // Name, Size, ModificationTime
    insertFileSorted(folder, "file2.txt", 300, 1600);
    insertFileSorted(folder, "file3.txt", 300, 1500); // Same size but older time
    insertFileSorted(folder, "file4.txt", 700, 1650);
    insertFileSorted(folder, "file5.txt", 300, 1700); // Same size but newer time

    // Display the list of files
    displayFiles(folder);

    // Delete all files with the smallest size
    deleteSmallestFiles(folder);

    // Display the list of files after deletion
    displayFiles(folder);

    return 0;
}