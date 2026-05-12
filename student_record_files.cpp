#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class student
{
public:
    int id;
    string name;
    string department;
    float gpa;

    void setdata(int i, string n, string d, float g)
    {
        id = i;
        name = n;
        department = d;
        gpa = g;
    }

    void display()
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "GPA: " << gpa << endl;
    }
};

void addstudent(string filename)
{
    ofstream file(filename, ios::app);
    if (!file)
    {
        cout << "Error opening file" << endl;
        return;
    }

    int id;
    string name, dept;
    float gpa;

    cout << "*************************" << endl;
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Department: ";
    getline(cin, dept);
    cout << "Enter CGPA: ";
    cin >> gpa;

    file << id << "," << name << "," << dept << "," << gpa << endl;

    cout << "Student added!" << endl;
    cout << "*************************" << endl;

    file.close();
}

void display(string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    int count = 0;
    cout << "*************************" << endl;
    cout << "All Students:" << endl;

    while (getline(file, line))
    {
        if (line == "")
            continue;

        student s;
        string word = "";
        string fields[4];
        int idx = 0;

        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ',')
            {
                fields[idx] = word;
                word = "";
                idx++;
            }
            else
            {
                word += line[i];
            }
        }
        fields[idx] = word;

        s.setdata(stoi(fields[0]), fields[1], fields[2], stof(fields[3]));
        s.display();
        cout << "-------------------------" << endl;
        count++;
    }

    if (count == 0)
        cout << "No records found!" << endl;

    cout << "*************************" << endl;
    file.close();
}

void searchStudent(string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    int searchID;
    cout << "*************************" << endl;
    cout << "Enter Student ID to search: ";
    cin >> searchID;

    string line;
    bool found = false;

    while (getline(file, line))
    {
        if (line == "")
            continue;

        string word = "";
        string fields[4];
        int idx = 0;

        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ',')
            {
                fields[idx] = word;
                word = "";
                idx++;
            }
            else
            {
                word += line[i];
            }
        }
        fields[idx] = word;

        if (stoi(fields[0]) == searchID)
        {
            student s;
            s.setdata(stoi(fields[0]), fields[1], fields[2], stof(fields[3]));
            cout << "Student found!" << endl;
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student not found!" << endl;

    cout << "*************************" << endl;
    file.close();
}

void updateStudent(string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    int updateID;
    cout << "*************************" << endl;
    cout << "Enter Student ID to update: ";
    cin >> updateID;

    string lines[100];
    int total = 0;
    string line;

    while (getline(file, line))
    {
        if (line != "")
            lines[total++] = line;
    }
    file.close();

    bool found = false;
    for (int i = 0; i < total; i++)
    {
        string word = "";
        string fields[4];
        int idx = 0;

        for (int j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] == ',')
            {
                fields[idx] = word;
                word = "";
                idx++;
            }
            else
            {
                word += lines[i][j];
            }
        }
        fields[idx] = word;

        if (stoi(fields[0]) == updateID)
        {
            string newName, newDept;
            float newGpa;

            cin.ignore();
            cout << "Enter new name: ";
            getline(cin, newName);
            cout << "Enter new department: ";
            getline(cin, newDept);
            cout << "Enter new GPA: ";
            cin >> newGpa;

            lines[i] = to_string(updateID) + "," + newName + "," + newDept + "," + to_string(newGpa);
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Student not found!" << endl;
        cout << "*************************" << endl;
        return;
    }

    ofstream outfile(filename);
    for (int i = 0; i < total; i++)
        outfile << lines[i] << endl;
    outfile.close();

    cout << "Record updated!" << endl;
    cout << "*************************" << endl;
}

void deletestudent(string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    int delID;
    cout << "*************************" << endl;
    cout << "Enter Student ID to delete: ";
    cin >> delID;

    string lines[100];
    int total = 0;
    string line;

    while (getline(file, line))
    {
        if (line != "")
            lines[total++] = line;
    }
    file.close();

    bool found = false;
    ofstream outfile(filename);

    for (int i = 0; i < total; i++)
    {
        string word = "";
        string fields[4];
        int idx = 0;

        for (int j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] == ',')
            {
                fields[idx] = word;
                word = "";
                idx++;
            }
            else
            {
                word += lines[i][j];
            }
        }
        fields[idx] = word;

        if (stoi(fields[0]) == delID)
        {
            found = true;
            continue;
        }
        outfile << lines[i] << endl;
    }
    outfile.close();

    if (found)
        cout << "Student deleted!" << endl;
    else
        cout << "Student not found!" << endl;

    cout << "*************************" << endl;
}

int main()
{
    string filename = "students.txt";
    bool run = true;

    do
    {
        string input;
        int action;

        cout << "*************************" << endl;
        cout << "Student Record Manager" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display All" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student" << endl;
        cout << "5. Delete Student" << endl;
        cout << "0. Exit" << endl;
        cout << "*************************" << endl;

        while (true)
        {
            cout << "Enter action (0-5): ";
            cin >> input;

            if (input == "0" || input == "1" || input == "2" ||
                input == "3" || input == "4" || input == "5")
            {
                action = stoi(input);
                break;
            }
            else
            {
                cout << "Invalid input! Try again." << endl;
            }
        }

        if (action == 0)
        {
            cout << "Program ended!!" << endl;
            run = false;
        }
        else if (action == 1)
            addstudent(filename);
        else if (action == 2)
            display(filename);
        else if (action == 3)
            searchStudent(filename);
        else if (action == 4)
            updateStudent(filename);
        else if (action == 5)
            deletestudent(filename);

    } while (run);

    return 0;
}