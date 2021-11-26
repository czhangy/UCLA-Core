//
//  fine.cpp
//  project_2
//
//  Created by Charles Zhang on 10/9/19.
//  Copyright © 2019 Charles Zhang. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
int main() {
    cout << "Defendant: ";
    string defendantName;
    getline(cin, defendantName);
    if (defendantName == "") { // Tests if the input for defendantName is an empty string
        cout << "---" << endl;
        cout << "You must enter a defendant name.";
    } else {
        cout << "Amount paid (in thousands): ";
        double amountPaid;
        cin >> amountPaid;
        if (amountPaid < 0) { // Tests if amountPaid is negative
            cout << "---" << endl;
            cout << "The amount paid must not be negative.";
        } else {
            cout << "Fake athlete? (y/n): ";
            string yesOrNo;
            cin.ignore(10000, '\n'); // Corrects the error created by the next getline consuming the newline
            getline(cin, yesOrNo);
            if ((yesOrNo != "y") && (yesOrNo != "n")) { // Tests if yesOrNo is a "y" or "n"
                cout << "---" << endl;
                cout << "You must enter y or n.";
            } else {
                double fine = 20.0;
                if (amountPaid > 40) {
                    fine += 26.4; // If over 40, immediately adds the 66% of 40 to the fine
                    if (amountPaid > 250) {
                        if (yesOrNo == "y") {
                            fine += 46.2; // If over 250 and a fake athlete, immediately adds 22% of 210 to the fine
                        } else {
                            fine += 21; // If over 250 and not a fake athlete, immediately adds 10% of 210 to the fine
                        }
                        fine += (amountPaid - 250) * 0.14; // Runs if amountPaid is over 250
                    } else { // Runs if amountPaid is between 40 and 250
                        if (yesOrNo == "y") { // Accounts for fake athlete
                            fine += (amountPaid - 40) * 0.22;
                        } else {
                            fine += (amountPaid - 40) * 0.10;
                        }
                    }
                } else {
                    fine += (0.66 * amountPaid); // Runs if amountPaid is less than 40
                }
                cout.setf(ios::fixed); // Sets to fixed notation
                cout.precision(1); // Sets to 1 decimal point
                cout << "---" << endl;
                cout << "The suggested fine for " << defendantName << " is $" << fine << " thousand."; // Final output for successful inputs
            }
        }
    }
}

