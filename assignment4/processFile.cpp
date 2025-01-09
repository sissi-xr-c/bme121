#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int nStudents(string filename) {
    ifstream fin;
    fin.open(filename);
    string line;
    int counter = 0;

    while (getline(fin, line)) {
        counter++;
    }

    fin.close();
    return counter;
}

string readLastname(ifstream &fin, int linenum) {
    string lname;
    string garbage;
    // garbage for the first #linenum-1# lines
    for (int i = 0; i < linenum; i++) {
        getline(fin, garbage, '\n');
    }
    // read line until ','
    getline(fin,lname, ',');

    return lname;
}

string readFirstname(ifstream &fin, int linenum) {
    string fname = "";

    readLastname(fin, linenum);
    fin.get();

    getline(fin, fname, ' ');

    return fname;
}

int nAssignments(string filename) {
    // open file
    ifstream fin;
    fin.open(filename);
    string garbage;
    char e;
    int counter = 1;
    // discard names
    readFirstname(fin,0);
    // count the number of white spaces between assignments
    while(fin.get(e)){
        if(e == ' ') {
            counter++;
        }
        else if (e == '\n') {
            break;
        }
    }

    fin.close();
    return counter;
}

void swapNames(string &first, string &second) {
    string temp = first;
    first = second;
    second = temp;
}

void swapNumbers(int &first, int &second) {
    int temp = first;
    first = second;
    second = temp;
}

void sortNames(string lnames[], string fnames[], int markorder[], const int nStudents) {

    for (int i = 0; i < nStudents; i++) {
        string smallest = lnames[i];

        for (int j = i + 1; j < nStudents; j++) {
            if (lnames[j] < smallest) {
                smallest = lnames[j];
                swapNames(lnames[j], lnames[i]);
                swapNames(fnames[j], fnames[i]);
                swapNumbers(markorder[j], markorder[i]);
            }
            else if (lnames[j] == smallest) {
                if (fnames[j] < fnames[i]) {
                    swapNames(lnames[j], lnames[i]);
                    swapNames(fnames[j], fnames[i]);
                    swapNumbers(markorder[j], markorder[i]);
                }
            }
        }

    }

}

string getMark(ifstream &fin) {

    string garbage;
    string mark = "";
    char e;

    // check if number starts
    while(fin.get(e)) {
        if(!isdigit(e)) {
            garbage += e;
        }
        else {
            mark += e;
            break;
        }
    }

    // check when number ends
    while(fin.get(e)) {
        if(isdigit(e)) {
            mark += e;
        }
        else {
            break;
        }
    }

    return mark;
}


void processFile(string filename) {

    // declare arrays and file stream
    ifstream fin;
    ofstream fout;
    string outfilename = filename+"-processed";
    int studentsNum = nStudents(filename);
    int assignmentsNum = nAssignments(filename);
    int markOrder[studentsNum];
    string lastNames[studentsNum];
    string firstNames[studentsNum];
    int marks[studentsNum][assignmentsNum];
    double average[assignmentsNum] = {0};

    // get last names
    for (int i = 0; i < studentsNum; i++) {
        fin.open(filename);
        lastNames[i] = readLastname(fin, i);
        fin.close();
    }

    // get first names
    for (int i = 0; i < studentsNum; i++) {
        fin.open(filename);
        firstNames[i] = readFirstname(fin, i);
        fin.close();
    }

    // set mark order to 0 --> #students-1
    for (int i = 0; i < studentsNum; i++) {
        markOrder[i] = i;
    }

    // sort names
    sortNames(lastNames, firstNames, markOrder, studentsNum);

    // get marks
    fin.open(filename);
    for (int i = 0; i < studentsNum; i++) {
        for (int j = 0; j < assignmentsNum; j++) {
            string mark = getMark(fin);
            int marknum = stoi(mark);
            marks[i][j] = marknum;
        }
    }
    fin.close();

    // calculate average
    for (int i = 0; i < studentsNum; i++) {
        for (int j = 0; j < assignmentsNum; j++) {
            average[j] +=  static_cast<double>(marks[i][j])/studentsNum;
        }
    }

    // output names and marks
    fout.open(outfilename);
    for (int i = 0; i < studentsNum; i++) {
        fout << lastNames[i] << ", " << firstNames[i];
        for (int j = 0; j < assignmentsNum; j++) {
            fout << " " << marks[markOrder[i]][j];
        }
        fout << endl;
    }

    // output average
    fout << "Average";
    fout.setf(ios::fixed);
    fout.precision(2);
    for (int i = 0; i < assignmentsNum; i++) {
        fout << " " << average[i];
        }

    fout << endl;
    fout.close();


}

/*int main() {
    string filename;
    cin >> filename;
    processFile(filename);
    return 0;
}
*/