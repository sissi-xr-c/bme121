#include <iostream>
#include <cstring>

using namespace std;

// initiate one for each student
struct studentRecord {
    int id;
    char *lastname;
    char *firstname;
    int *quizMarks;
};

// initiate one for entire student list
struct studentList {
    studentRecord *sr;
    studentList *next;
};

/*****************************************************************/
/* Function declarations. 5 functions in total.                  */
/*****************************************************************/
/*
    addStudent()

    Arguments:
       - l: a pointer to a list of studentRecords, possibly nullptr
       - lastname: Last name of a new student record to be added
       - firstname: First name of the new student
       - quizMarks: the marks for this student on each quiz; an integer
                    between 0 and 100, inclusive
       - nQuizzes: the number of quizzes.

    This function should (i) generate a unique student ID, which is a
    positive integer, for this new student, and, (ii) add this student
    to the list.

    Note that lastname and firstname need to be converted to C-style
    char * strings from the arguments of type string.

    E.g., if we call this function with l == nullptr and a student whose
    lastname, firstname is Smith, Alice, and then with a student whose
    lastname, firstname is Connick Jr., Harry, l should contain the
    record for Connick Jr. before Smith's.
*/
void addStudent(studentList *& l,
                string lastname,
                string firstname,
                int quizMarks[],
                int nQuizzes);

/*
    removeStudent()

    Arguments:
       - l: a pointer to a list of studentRecords, possibly nullptr
       - studentID: an ID of a student to be removed

    If a student record with that ID exists in the list, remove it.
    If not, leave the list unchanged. If this is the only student
    record in the list, assign nullptr to l.

    MEMORY LEAK WARNING: you should carefully deallocate the space
    for the removed student. If e is of type studentList *, the
    right way to deallocate:
        delete [](e->sr->lastname);
        delete [](e->sr->firstname);
        delete [](e>sr->quizMarks);
        delete e->sr;
        delete e;
*/
void removeStudent(studentList *& l,
                   int studentID);

/*
    findStudentByID()

    Arguments:
       - l: a pointer to a list of studentRecords, possibly nullptr
       - studentID: an ID of a student to be removed

    If there is a student with that studentID, return a pointer 
    to that student's record. Return nullptr if no student with
    that studentID.
*/
studentRecord *findStudentByID(const studentList *l,
                               int studentID);

/*
    findStudentsByLastName()

    Arguments:
       - l: a pointer to a list of studentRecords, possibly nullptr
       - lasname: Last name of the students to find
       - nQuizzes: the number of quizzes per student (so we know what the
                   valid indices for quizMarks[] is in each student record

    Reurns a pointer to a newly constructed student list of all students
    with that lastname. Note that the caller may deallocate the space
    for this new student list after you return.

    (Note: you should be able to use your addStudent() function to
           populate this new list. But then you should be careful to
           have the correct id for each student in what you return --- it
           should match what's in the argument l.)
*/
studentList *findStudentsByLastName(const studentList *l,
                                    string lastname,
                                    int nQuizzes);

/* quizAverage()

    Arguments:
       - l: a pointer to a list of studentRecords, possibly nullptr
       - quizNum: the quiz for which we want the average

    Return a double, which is the average across all students in
    quizNum. Assume that quizNum is a valid quiz number between 0
    and the # quizzes - 1. That is, you can simply use quizNum
    as as index into the quizMarks field for a student.
*/
double quizAverage(const studentList *l, int quizNum);
