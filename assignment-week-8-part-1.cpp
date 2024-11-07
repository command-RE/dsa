#include <iostream>
#include <cstring>

// Structure to store date
struct Ngay
{
    int ngay, thang, nam;
};

// Structure to store student information
struct SinhVien
{
    char maSV[8];     // Student ID
    char hoTen[50];   // Full name
    int gioiTinh;     // Gender
    Ngay ngaySinh;    // Date of birth
    char diaChi[100]; // Address
    char lop[12];     // Class
    char khoa[7];     // Department
};

// Node structure for linked list
struct Node
{
    SinhVien data; // Student data
    Node *link;    // Pointer to next node
};

// List structure to manage the linked list
struct List
{
    Node *first; // Pointer to the first node
    Node *last;  // Pointer to the last node
};

// Function to initialize the list
void initializeList(List &list)
{
    list.first = nullptr;
    list.last = nullptr;
}

// Function to create a new node with student data
Node *createNode(const SinhVien &sv)
{
    Node *node = new Node;
    node->data = sv;
    node->link = nullptr;
    return node;
}

// Function to add a student to the end of the list
void addStudent(List &list, const SinhVien &sv)
{
    Node *node = createNode(sv);
    if (list.first == nullptr)
    {
        list.first = list.last = node;
    }
    else
    {
        list.last->link = node;
        list.last = node;
    }
}

// Function to print a student's information
void printStudent(const SinhVien &sv)
{
    std::cout << "MaSV: " << sv.maSV << ", HoTen: " << sv.hoTen << ", GioiTinh: " << (sv.gioiTinh ? "Nam" : "Nu")
              << ", NgaySinh: " << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam
              << ", DiaChi: " << sv.diaChi << ", Lop: " << sv.lop << ", Khoa: " << sv.khoa << std::endl;
}

// Function to print all students in the list
void printList(const List &list)
{
    for (Node *current = list.first; current != nullptr; current = current->link)
    {
        printStudent(current->data);
    }
}

// Function to add a student to the list in sorted order by student ID
void addStudentSorted(List &list, const SinhVien &sv)
{
    Node *node = createNode(sv);

    // Handle the case where the list is empty or the new node should be inserted at the front
    if (list.first == nullptr || strcmp(list.first->data.maSV, sv.maSV) > 0)
    {
        node->link = list.first;
        list.first = node;
        if (list.last == nullptr)
        {
            list.last = node;
        }
    }
    else
    {
        Node *current = list.first;
        while (current->link != nullptr && strcmp(current->link->data.maSV, sv.maSV) < 0)
        {
            current = current->link;
        }
        node->link = current->link;
        current->link = node;
        if (node->link == nullptr)
        {
            list.last = node;
        }
    }
}

// Helper function to check if two students have the same date of birth
bool haveSameDOB(const SinhVien &sv1, const SinhVien &sv2)
{
    return sv1.ngaySinh.ngay == sv2.ngaySinh.ngay &&
           sv1.ngaySinh.thang == sv2.ngaySinh.thang &&
           sv1.ngaySinh.nam == sv2.ngaySinh.nam;
}

// Function to print students with the same date of birth
#include <set>

void printStudentsWithSameDOB(const List &list)
{
    bool found = false;
    std::set<std::string> printedStudents;
    for (Node *i = list.first; i != nullptr; i = i->link)
    {
        bool hasSameDOB = false;
        for (Node *j = i->link; j != nullptr; j = j->link)
        {
            if (haveSameDOB(i->data, j->data))
            {
                if (!hasSameDOB && printedStudents.find(i->data.maSV) == printedStudents.end())
                {
                    printStudent(i->data);
                    printedStudents.insert(i->data.maSV);
                    hasSameDOB = true;
                    found = true;
                }
                if (printedStudents.find(j->data.maSV) == printedStudents.end())
                {
                    printStudent(j->data);
                    printedStudents.insert(j->data.maSV);
                }
            }
        }
    }
    if (!found)
    {
        std::cout << "No students with the same date of birth found." << std::endl;
    }
}

// Function to remove a student node from the list
void removeNode(List &list, Node *prev, Node *current)
{
    if (prev == nullptr)
    {
        list.first = current->link;
    }
    else
    {
        prev->link = current->link;
    }
    if (current == list.last)
    {
        list.last = prev;
    }
    delete current;
}

// Function to remove students with the same date of birth
void removeStudentsWithSameDOB(List &list)
{
    Node *prev = nullptr;
    Node *current = list.first;

    while (current != nullptr)
    {
        bool hasSameDOB = false;
        Node *runnerPrev = current;
        Node *runner = current->link;

        while (runner != nullptr)
        {
            if (haveSameDOB(current->data, runner->data))
            {
                hasSameDOB = true;
                Node *temp = runner;
                runner = runner->link;
                removeNode(list, runnerPrev, temp);
            }
            else
            {
                runnerPrev = runner;
                runner = runner->link;
            }
        }

        if (hasSameDOB)
        {
            Node *temp = current;
            current = current->link;
            removeNode(list, prev, temp);
        }
        else
        {
            prev = current;
            current = current->link;
        }
    }
}

int main()
{
    List studentList;
    initializeList(studentList);

    // Sample student data
    SinhVien sv1 = {"SV001", "Nguyen Van A", 1, {1, 1, 2000}, "123 ABC Street", "CTK42", "CNTT"};
    SinhVien sv2 = {"SV002", "Tran Thi B", 0, {1, 1, 2000}, "456 DEF Street", "CTK42", "CNTT"};
    SinhVien sv3 = {"SV003", "Le Van C", 1, {2, 2, 2001}, "789 GHI Street", "CTK43", "CNTT"};
    SinhVien sv4 = {"SV004", "Pham Thi D", 0, {1, 1, 2000}, "101 JKL Street", "CTK42", "CNTT"};

    // Adding students to the list
    addStudent(studentList, sv1);
    addStudent(studentList, sv2);
    addStudent(studentList, sv3);
    addStudent(studentList, sv4);

    std::cout << "Student List:" << std::endl;
    printList(studentList);

    std::cout << "\nStudents with the same date of birth:" << std::endl;
    printStudentsWithSameDOB(studentList);

    std::cout << "\nRemoving students with the same date of birth..." << std::endl;
    removeStudentsWithSameDOB(studentList);

    std::cout << "\nStudent List after removal:" << std::endl;
    printList(studentList);

    return 0;
}