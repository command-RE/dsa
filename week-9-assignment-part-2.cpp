#include <iostream>
#include <string>
using namespace std;

// Structure for a node in the linked list
struct Node
{
    string word;
    int count;
    Node *next;
};

// Function to create a new node
Node *createNode(const string &word)
{
    Node *newNode = new Node;
    newNode->word = word;
    newNode->count = 1;
    newNode->next = nullptr;
    return newNode;
}

// Function to insert or update a word in the linked list
void insertOrUpdate(Node *&head, const string &word)
{
    Node *current = head;
    Node *prev = nullptr;

    while (current != nullptr)
    {
        if (current->word == word)
        {
            current->count++;
            return;
        }
        prev = current;
        current = current->next;
    }

    Node *newNode = createNode(word);
    if (prev == nullptr)
    {
        head = newNode;
    }
    else
    {
        prev->next = newNode;
    }
}

// Function to find the most frequent word
string findMostFrequent(Node *head)
{
    if (!head)
        return "";

    Node *current = head;
    string mostFrequentWord = current->word;
    int maxCount = current->count;

    while (current)
    {
        if (current->count > maxCount)
        {
            maxCount = current->count;
            mostFrequentWord = current->word;
        }
        current = current->next;
    }

    return mostFrequentWord;
}

// Function to remove compound words
void removeCompoundWords(Node *&head)
{
    Node *current = head;
    Node *prev = nullptr;

    while (current && current->next)
    {
        if (current->word == current->next->word)
        {
            Node *temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

// Function to count unique words
int countUniqueWords(Node *head)
{
    int count = 0;
    Node *current = head;

    while (current)
    {
        count++;
        current = current->next;
    }

    return count;
}

// Function to delete the linked list and free memory
void deleteList(Node *&head)
{
    Node *current = head;
    while (current)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

int main()
{
    Node *head = nullptr;
    string sentence = "xanh xanh dep dep dep tuoi tuoi tuoi tuoi";

    // Split sentence into words and insert/update in the linked list
    size_t pos = 0;
    string delimiter = " ";
    while ((pos = sentence.find(delimiter)) != string::npos)
    {
        string word = sentence.substr(0, pos);
        insertOrUpdate(head, word);
        sentence.erase(0, pos + delimiter.length());
    }
    insertOrUpdate(head, sentence); // Insert last word

    // Find and display the most frequent word
    string mostFrequent = findMostFrequent(head);
    cout << "Most frequent word: " << mostFrequent << endl;

    // Remove compound words
    removeCompoundWords(head);

    // Count and display the number of unique words
    int uniqueWordsCount = countUniqueWords(head);
    cout << "Number of unique words: " << uniqueWordsCount << endl;

    // Clean up memory
    deleteList(head);

    return 0;
}