#include <iostream>
#include <string>

struct File
{
    std::string name;
    std::string creationDate;
    int size; // in MB
    File *next;
};

class Directory
{
private:
    File *head;

public:
    Directory() : head(nullptr) {}

    // Function to insert a file in chronological order
    void insertFile(const std::string &name, const std::string &creationDate, int size)
    {
        File *newFile = new File{name, creationDate, size, nullptr};

        if (!head || head->creationDate > creationDate)
        {
            newFile->next = head;
            head = newFile;
        }
        else
        {
            File *current = head;
            while (current->next && current->next->creationDate <= creationDate)
            {
                current = current->next;
            }
            newFile->next = current->next;
            current->next = newFile;
        }
    }

    // Function to calculate the total size of all files
    int calculateTotalSize() const
    {
        int totalSize = 0;
        File *current = head;
        while (current)
        {
            totalSize += current->size;
            current = current->next;
        }
        return totalSize;
    }

    // Function to backup files to a 32GB USB drive
    void backupFiles()
    {
        const int maxSize = 32000; // 32GB in MB
        int currentSize = calculateTotalSize();

        while (currentSize > maxSize)
        {
            removeSmallestFile();
            currentSize = calculateTotalSize();
        }
    }

    // Helper function to remove the smallest file
    void removeSmallestFile()
    {
        if (!head)
            return;

        File *smallest = head;
        File *prev = nullptr;
        File *current = head;

        while (current->next)
        {
            if (current->next->size < smallest->size)
            {
                smallest = current->next;
                prev = current;
            }
            current = current->next;
        }

        if (smallest == head)
        {
            head = head->next;
        }
        else
        {
            prev->next = smallest->next;
        }

        delete smallest;
    }

    // Function to display all files
    void displayFiles() const
    {
        File *current = head;
        while (current)
        {
            std::cout << "File: " << current->name
                      << ", Date: " << current->creationDate
                      << ", Size: " << current->size << "MB" << std::endl;
            current = current->next;
        }
    }

    // Destructor to free memory
    ~Directory()
    {
        while (head)
        {
            File *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{
    Directory directory;

    directory.insertFile("file1.txt", "2022-01-01", 500);
    directory.insertFile("file2.txt", "2022-01-05", 1500);
    directory.insertFile("file3.txt", "2022-01-03", 750);

    std::cout << "Files in directory:" << std::endl;
    directory.displayFiles();

    std::cout << "Total size: " << directory.calculateTotalSize() << "MB" << std::endl;

    directory.backupFiles();

    std::cout << "After backup, files in directory:" << std::endl;
    directory.displayFiles();

    return 0;
}