#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// Structure for a tree node
struct TreeNode
{
    string title;                // Title of the chapter/section
    int pageNumber;              // Starting page number
    vector<TreeNode *> children; // Children nodes (subsections)

    // Constructor for the tree node
    TreeNode(string t, int p) : title(t), pageNumber(p) {}
};

// Function to count the number of chapters (top-level nodes)
int countChapters(TreeNode *root)
{
    if (!root)
        return 0;
    return root->children.size();
}

// Helper function to find the longest chapter (based on title length)
void findLongestChapter(TreeNode *root, string &longestTitle)
{
    if (!root)
        return;

    if (root->title.length() > longestTitle.length())
    {
        longestTitle = root->title;
    }

    for (TreeNode *child : root->children)
    {
        findLongestChapter(child, longestTitle);
    }
}

// Function to search for an item and delete it
bool searchAndDelete(TreeNode *root, const string &item, int &removedPages)
{
    if (!root)
        return false;

    // Iterate through the children of the current node
    for (auto it = root->children.begin(); it != root->children.end(); ++it)
    {
        if ((*it)->title == item)
        {
            // Found the item to delete
            removedPages = (*it)->pageNumber;
            delete *it;               // Free memory
            root->children.erase(it); // Remove from children
            return true;
        }
        // Recursively search in the child node
        if (searchAndDelete(*it, item, removedPages))
        {
            return true;
        }
    }
    return false;
}

// Function to update page numbers recursively
void updatePageNumbers(TreeNode *root, int pageOffset)
{
    if (!root)
        return;

    root->pageNumber += pageOffset;
    for (TreeNode *child : root->children)
    {
        updatePageNumbers(child, pageOffset);
    }
}

// Function to print the table of contents (for testing purposes)
void printTableOfContents(TreeNode *root, int depth = 0)
{
    if (!root)
        return;

    for (int i = 0; i < depth; ++i)
        cout << "  ";
    cout << root->title << " (Page: " << root->pageNumber << ")" << endl;

    for (TreeNode *child : root->children)
    {
        printTableOfContents(child, depth + 1);
    }
}

int main()
{
    // Creating the tree structure
    TreeNode *book = new TreeNode("Book Title", 0);

    // Adding chapters
    TreeNode *chapter1 = new TreeNode("Chapter 1: Introduction", 1);
    TreeNode *chapter2 = new TreeNode("Chapter 2: Advanced Topics", 20);

    // Adding sections to Chapter 1
    chapter1->children.push_back(new TreeNode("Section 1.1: Overview", 2));
    chapter1->children.push_back(new TreeNode("Section 1.2: Background", 5));

    // Adding subsections to Section 1.1
    chapter1->children[0]->children.push_back(new TreeNode("Subsection 1.1.1: History", 3));
    chapter1->children[0]->children.push_back(new TreeNode("Subsection 1.1.2: Concepts", 4));

    // Adding sections to Chapter 2
    chapter2->children.push_back(new TreeNode("Section 2.1: Techniques", 21));
    chapter2->children.push_back(new TreeNode("Section 2.2: Applications", 25));

    // Add chapters to the book
    book->children.push_back(chapter1);
    book->children.push_back(chapter2);

    // Print the initial table of contents
    cout << "Initial Table of Contents:" << endl;
    printTableOfContents(book);

    // Task 1: Count the number of chapters
    cout << "\nNumber of chapters: " << countChapters(book) << endl;

    // Task 2: Find the longest chapter title
    string longestTitle = "";
    findLongestChapter(book, longestTitle);
    cout << "Longest chapter title: " << longestTitle << endl;

    // Task 3: Search for and delete an item
    string itemToDelete = "Section 1.1: Overview";
    int removedPages = 0;
    if (searchAndDelete(book, itemToDelete, removedPages))
    {
        cout << "\nDeleted item: " << itemToDelete << endl;

        // Update page numbers after deletion
        updatePageNumbers(book, -removedPages);
        cout << "Updated page numbers after deletion." << endl;
    }
    else
    {
        cout << "\nItem not found: " << itemToDelete << endl;
    }

    // Print the updated table of contents
    cout << "\nUpdated Table of Contents:" << endl;
    printTableOfContents(book);

    // Clean up memory (manual deletion for simplicity)
    delete book;

    return 0;
}