#include <iostream>
#include <cmath>
using namespace std;

int main() {

    //declare variables
    double a, i;
    int t;
    string command;

    //user input
    cin >> a >> i >> t;
    double m = i / (12*100);
    double p = (a * m * pow(m+ 1, t)) / (pow(m + 1, t) - 1);
    cin >> command;

    //do the thing
    while (command != "e") {
        if (command == "p") {
            //print
            cout.setf(ios::fixed);
            cout.setf(ios::showpoint);
            cout.precision(2);
            cout << p << endl;
            cin >> command;
        }
        else if (command == "d") {
            double month;
            cin >> month;
            //set initial values
            double pOutstanding = a;
            double interest;
            double pRemaining = a;
            //compound interest for # of months
            for (int i = 0; i < month; i++) {
                //set current month's outstanding value to last month's remaining
                pOutstanding = pRemaining;
                interest = pOutstanding * m;
                pRemaining = pOutstanding + interest - p;
            }
            cout.setf(ios::fixed);
            cout.setf(ios::showpoint);
            cout.precision(2);
            cout << pOutstanding << " " << interest << " " << pRemaining << endl;
            cin >> command;
        }
    }
    return 0;
}
