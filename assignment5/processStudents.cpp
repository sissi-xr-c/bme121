#include "processStudents.h"
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
   This file should compile with processStudentsSampleMain.cpp.
   Of course, it does not implement the required functionality.
*/

void addStudent(studentList *& l, string lastname, string firstname, int quizMarks[], int nQuizzes)
{
    // set this list item into address of l.next (head), then change l into new list item
    studentList *listitem = new studentList;

    studentRecord *newStudent = new studentRecord;
    newStudent -> id = rand(); // how to set to random integer?

    // add last name
    newStudent -> lastname = new char[lastname.length() + 1];
    strcpy(newStudent -> lastname, lastname.c_str());

    // add first name
    newStudent -> firstname = new char[firstname.length() + 1];
    for (int i = 0; i < firstname.length(); i++) {
        newStudent -> firstname[i] = firstname[i];
    }
    newStudent -> firstname[firstname.length()] = '\0';

    // add quiz marks
    newStudent -> quizMarks = new int[nQuizzes + 1];
    for (int i = 0; i < nQuizzes; i++) {
        newStudent -> quizMarks[i] = quizMarks[i];
    }
    newStudent -> quizMarks[nQuizzes] = '\0';

    // add student to linked list
    listitem -> sr = newStudent;
    listitem -> next = l; // when pointer is done reading this item, it reads the next item
    l = listitem; // sets this as the head

}

// adds student but with existing id
void addStudent(studentList *& l, string lastname, string firstname, int quizMarks[], int nQuizzes, int id)
{
    // set l.next to address of previous item, then change l (head) into new list item
    studentList *listitem = new studentList;

    studentRecord *newStudent = new studentRecord;
    newStudent -> id = id;

    // add last name
    newStudent -> lastname = new char[lastname.length() + 1];
    for (int i = 0; i < lastname.length(); i++) {
        newStudent -> lastname[i] = lastname[i];
    }
    newStudent -> lastname[lastname.length()] = '\0';

    // add first name
    newStudent -> firstname = new char[firstname.length() + 1];
    for (int i = 0; i < firstname.length(); i++) {
        newStudent -> firstname[i] = firstname[i];
    }
    newStudent -> firstname[firstname.length()] = '\0';

    // add quiz marks
    newStudent -> quizMarks = new int[nQuizzes + 1];
    for (int i = 0; i < nQuizzes; i++) {
        newStudent -> quizMarks[i] = quizMarks[i];
    }
    newStudent -> quizMarks[nQuizzes] = '\0';

    // add student to linked list
    listitem -> sr = newStudent;
    listitem -> next = l; // when pointer is done reading this item, it reads the next item
    l = listitem; // sets this as the head

}

void removeStudent(studentList *& l, int studentID)
{
    // set to address previous to head (nothing there)
    studentList *previous = nullptr;
    // set to address of head
    studentList *current = l;

    while (current != nullptr) {
        if (current -> sr -> id == studentID) {
            // remove
            if (previous == nullptr) { // if current value is at head of the list
                l = current -> next;
            }
            else { // if current value is in the middle of the list
                previous -> next = current -> next; // pointer skips current value
            }

            // deallocate all memory for current in opposite order of allocation
            delete [] current -> sr -> lastname;
            delete [] current -> sr -> firstname;
            delete [] current -> sr -> quizMarks;
            delete current -> sr;
            delete current;
        }

        else { // move forward
            previous = current;
        }

        // if we're in the middle of the list
        if (previous != nullptr) {
            current = previous -> next;
        }
        // if we're at the front of the list
        else {
            current = l -> next;
        }
    }

}

studentRecord *findStudentByID(const studentList *l, int studentID)
{
    for (const studentList *temp = l; temp != nullptr; temp = temp -> next) {
        if (temp -> sr -> id == studentID) {
            return temp -> sr;
        }
    }
    return nullptr;
}

studentList *findStudentsByLastName(const studentList *l, string lastname, int nQuizzes)
{
    studentList *lNameList = nullptr;
    bool found = false;
    for (const studentList *temp = l; temp != nullptr; temp = temp -> next) {
        if (temp -> sr -> lastname == lastname) {
            found = true;
            string firstname = temp -> sr -> firstname;
            int quizMarks[nQuizzes];
            for (int i = 0; i < nQuizzes; i++) {
                quizMarks[i] = temp -> sr -> quizMarks[i];
            }
            int id = temp -> sr -> id;
            addStudent(lNameList, lastname, firstname, quizMarks, nQuizzes, id);
        }
    };

    if (found) {
        return lNameList;
    }
    return nullptr;
}

double quizAverage(const studentList *l, int quizNum)
{
    double average = 0;
    double counter = 0;
    for (const studentList *temp = l; temp != nullptr; temp = temp -> next) {
        average += temp -> sr -> quizMarks[quizNum];
        counter++;
    }

    average /= counter;

    return average;
}
