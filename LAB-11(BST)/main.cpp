#include <iostream>
#include <string>

using namespace std;

class StudentNode
{
public:
    int rollNo;
    string name;
    double cgpa;
    StudentNode *left;
    StudentNode *right;

    StudentNode(int r, string n, double c) : rollNo(r), name(n), cgpa(c), left(nullptr), right(nullptr) {}
};

class StudentBST
{
private:
    StudentNode *root;
    void destroy(StudentNode *s)
    {
        if (s != nullptr)
        {
            destroy(s->left);
            destroy(s->right);
            delete s;
        }
    }

    void InOrder(StudentNode *s)
    {
        if (s != nullptr)
        {
            InOrder(s->left);
            cout << "Roll No: " << s->rollNo << ", Name: " << s->name << ", CGPA: " << s->cgpa << endl;
            InOrder(s->right);
        }
    }

    StudentNode *findMin(StudentNode *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    StudentNode *removeHelper(StudentNode *root, int rn, bool &found)
    {
        if (root == nullptr)
        {
            return root;
        }

        if (rn < root->rollNo)
        {
            root->left = removeHelper(root->left, rn, found);
        }
        else if (rn > root->rollNo)
        {
            root->right = removeHelper(root->right, rn, found);
        }
        else
        {
            found = true;

            if (root->left == nullptr)
            {
                StudentNode *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                StudentNode *temp = root->left;
                delete root;
                return temp;
            }
            StudentNode *temp = findMin(root->right);
            root->rollNo = temp->rollNo;
            root->name = temp->name;
            root->cgpa = temp->cgpa;
            root->right = removeHelper(root->right, temp->rollNo, found);
        }
        return root;
    }

    void displayInRangeHelper(StudentNode *s, double start, double end)
    {
        if (s != nullptr)
        {
            displayInRangeHelper(s->left, start, end);
            if (s->cgpa >= start && s->cgpa <= end)
            {
                cout << "Roll No: " << s->rollNo << ", Name: " << s->name << ", CGPA: " << s->cgpa << endl;
            }
            displayInRangeHelper(s->right, start, end);
        }
    }

public:
    StudentBST() : root(nullptr) {}

    ~StudentBST()
    {
        destroy(root);
    }

    bool insert(int rn, string n, double c)
    {
        StudentNode *newNode = new StudentNode(rn, n, c);

        if (root == nullptr)
        {
            root = newNode;
            return true;
        }

        StudentNode *current = root;
        StudentNode *parent = nullptr;

        while (current != nullptr)
        {
            parent = current;
            if (rn == current->rollNo)
            {
                delete newNode; 
                return false;
            }
            else if (rn < current->rollNo)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        if (rn < parent->rollNo)
        {
            parent->left = newNode;
        }
        else
        {
            parent->right = newNode;
        }
        return true;
    }

    bool search(int rn)
    {
        StudentNode *current = root;
        while (current != nullptr)
        {
            if (current->rollNo == rn)
            {
                cout << "Student Found - Roll No: " << current->rollNo
                     << ", Name: " << current->name
                     << ", CGPA: " << current->cgpa << endl;
                return true;
            }
            else if (rn < current->rollNo)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        cout << "Student with Roll No " << rn << " not found." << endl;
        return false;
    }

  
    void InOrder()
    {
        cout << "--- Student List (Sorted by Roll No) ---" << endl;
        InOrder(root);
        cout << "----------------------------------------" << endl;
    }

  
    bool remove(int rn)
    {
        bool found = false;
        root = removeHelper(root, rn, found);
        if (found)
        {
            cout << "Student with Roll No " << rn << " deleted." << endl;
        }
        else
        {
            cout << "Student with Roll No " << rn << " not found, cannot delete." << endl;
        }
        return found;
    }

    void displayInRange(double cgpaStart, double cgpaEnd)
    {
        cout << " Students with CGPA between " << cgpaStart << " and " << cgpaEnd << " ---" << endl;
        displayInRangeHelper(root, cgpaStart, cgpaEnd);
        cout << "--------------------------" << endl;
    }
};

int main()
{
    StudentBST tree;
    int choice;
    int rn;
    string name;
    double cgpa;
    double start, end;

    do
    {
        cout << "\n--- Student BST Menu ---" << endl;
        cout << "1. Insert a new student" << endl;
        cout << "2. Search for a student" << endl;
        cout << "3. See the list of students" << endl;
        cout << "4. Remove a student" << endl;
        cout << "5. Display students in CGPA range" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Roll No: ";
            cin >> rn;
            cin.ignore(); // clear newline
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter CGPA: ";
            cin >> cgpa;
            if (tree.insert(rn, name, cgpa))
            {
                cout << "Student inserted successfully." << endl;
            }
            else
            {
                cout << "Error: Student with this Roll No already exists." << endl;
            }
            break;
        case 2:
            cout << "Enter Roll No to search: ";
            cin >> rn;
            tree.search(rn);
            break;
        case 3:
            tree.InOrder();
            break;
        case 4:
            cout << "Enter Roll No to remove: ";
            cin >> rn;
            tree.remove(rn);
            break;
        case 5:
            cout << "Enter min CGPA: ";
            cin >> start;
            cout << "Enter max CGPA: ";
            cin >> end;
            tree.displayInRange(start, end);
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}