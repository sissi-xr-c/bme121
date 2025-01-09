#include "processStudents.h"
#include <ctime>
#include <cstdlib>

void getSomeQuizMarks(int m[], int nq) {
    for(int i = 0; i < nq; i++)
        m[i] = rand() % 101;
}

void printStudentList(string preamble, const studentList *mylist, int nQuizzes) {
    cout << "Contents of " << preamble << ":" << endl;

    if(mylist == nullptr) {
        cout << '\t' << "<empty>" << endl; return;
    }

    for(const studentList *it = mylist; it != nullptr; it = it->next) {
        cout << '\t'; // Tab
        cout << (it->sr->id) << "; ";
        cout << (it->sr->lastname) << ", ";
        cout << (it->sr->firstname) << "; ";
        for(int i = 0; i < nQuizzes; i++) {
            cout << ((it->sr->quizMarks)[i]) << " ";
        }
        cout << endl;
    }
}

void deallocateStudentList(studentList *l) {
    for(studentList *it = l; it != nullptr; ) {
        studentList *toDelete = it;
        it = it->next;
        delete [] (toDelete->sr->lastname);
        delete [] (toDelete->sr->firstname);
        delete [] (toDelete->sr->quizMarks);
        delete (toDelete->sr);
        delete toDelete;
    }
}

/*
    The following is the output of a run of this main() on my implementation of the 5 functions.

    Contents of mylist:
	1; Smith, Alice; 76 93 29 43 58 96 85 64
    Contents of mylist:
	<empty>
    Contents of mylist:
	3; Wang, Ruohai; 91 59 59 66 91 64 48 32
	2; Martin, Paul; 90 69 54 15 78 38 17 54
	1; Smith, Alice; 31 57 16 59 48 58 80 5
    Contents of mylist:
	5; Smith, Bob; 83 60 96 30 84 75 35 40
	4; Davis Jr., Sammy; 56 44 76 81 39 60 44 70
	3; Wang, Ruohai; 91 59 59 66 91 64 48 32
	1; Smith, Alice; 31 57 16 59 48 58 80 5
    Contents of smiths:
	1; Smith, Alice; 31 57 16 59 48 58 80 5
	5; Smith, Bob; 83 60 96 30 84 75 35 40
    Contents of mylist:
	4; Davis Jr., Sammy; 56 44 76 81 39 60 44 70
	3; Wang, Ruohai; 91 59 59 66 91 64 48 32
    Average on quiz # 2 = 67.5
*/

int main() {
    srand(time(0));

    int nQuizzes = (rand() % 4) + 5; // Between 5 and 8 quizzes
    studentList *mylist = nullptr;

    int quizMarks[nQuizzes];

    getSomeQuizMarks(quizMarks, nQuizzes);
    addStudent(mylist, "Smith", "Alice", quizMarks, nQuizzes);

    string preamble = "mylist";
    printStudentList(preamble, mylist, nQuizzes);

    removeStudent(mylist, 1);
    printStudentList(preamble, mylist, nQuizzes);

    getSomeQuizMarks(quizMarks, nQuizzes);
    for (int i = 0; i < nQuizzes; i++) {
        cout << quizMarks[i] << " ";
    }
    cout << endl;
    addStudent(mylist, "Smith", "Alice", quizMarks, nQuizzes);
    getSomeQuizMarks(quizMarks, nQuizzes);
    for (int i = 0; i < nQuizzes; i++) {
        cout << quizMarks[i] << " ";
    }
    cout << endl;
    addStudent(mylist, "Martin", "Paul", quizMarks, nQuizzes);
    getSomeQuizMarks(quizMarks, nQuizzes);
    addStudent(mylist, "Wang", "Ruohai", quizMarks, nQuizzes);

    printStudentList(preamble, mylist, nQuizzes);

    removeStudent(mylist, 2);
    removeStudent(mylist, 10);
    getSomeQuizMarks(quizMarks, nQuizzes);
    addStudent(mylist, "Davis Jr.", "Sammy", quizMarks, nQuizzes);
    getSomeQuizMarks(quizMarks, nQuizzes);
    addStudent(mylist, "Smith", "Bob", quizMarks, nQuizzes);

    printStudentList(preamble, mylist, nQuizzes);

    studentList *smiths = findStudentsByLastName(mylist, "Smith", nQuizzes);
    preamble = "smiths";
    printStudentList(preamble, smiths, nQuizzes);

    for(const studentList *it = smiths; it != nullptr; it = it->next) {
        removeStudent(mylist, it->sr->id);
    }
    preamble = "mylist";
    printStudentList(preamble, mylist, nQuizzes);

    deallocateStudentList(smiths);

    int quizNum = rand() % nQuizzes;
    double avg = quizAverage(mylist, quizNum);
    cout << "Average on quiz # " << quizNum << " = " << avg << endl;

    deallocateStudentList(mylist);

    return 0;
}
