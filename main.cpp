#include <iostream>
#include <map>
#include <set>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "not enough arguments" << endl;
        return 0;
    }

    string number = argv[1];

    //create a map for the numeral values
    map<char, int> symbolMap;
    symbolMap['I'] = 1;
    symbolMap['V'] = 5;
    symbolMap['X'] = 10;
    symbolMap['L'] = 50;
    symbolMap['C'] = 100;
    symbolMap['D'] = 500;
    symbolMap['M'] = 1000;


    //check to see if it is a number or a numeral
    bool isNumber = true;
    bool isNumeral = true;
    for (int i = 0; i < number.length(); i++) {
        char thisChar = number.at(i);
        if (isdigit(thisChar)) {
            isNumeral = false;
        } else {
            isNumber = false;
            if (symbolMap.find(thisChar) == symbolMap.end()) {
                //did not find a symbol
                isNumeral = false;
            }
        }
    }

    //invalid input (will catch negetive numbers because our checker checks '-')
    if (!isNumeral && !isNumber) {
        cout << "invalid input, please try again" << endl;
        return 0;
    }

    if (isNumber) {
        //cout << "Thank you for putting in a number" << endl;

        int num = stoi(number);
        string numeral = "";

        //CAREFUL ABOUT GOING OVER THE M LIMIT!!!!
        if (num > 3999) {
            cout << "You have inputted a number over this converters limit of 3999" << endl;
            cout << "The number you input is " + number << endl;
        }

        //will be going through each digit individually, going from smallest (right) to largest (left)
        int tenMultiplier = 0;
        for (int i = number.length() - 1; i >= 0; i--) {
            char thisCharNum = number.at(i);
            int thisNum = thisCharNum - '0';
            string baseString;
            string midString;
            string topString;

            //get the mapped characters
            if (tenMultiplier == 0) {
                baseString = "I";
                midString = "V";
                topString = "X";
            } else if (tenMultiplier == 1) {
                baseString = "X";
                midString = "L";
                topString = "C";
            } else if (tenMultiplier == 2) {
                baseString = "C";
                midString = "D";
                topString = "M";
            } else if (tenMultiplier >= 3) {
                baseString = "M";
                midString = "";
                topString = "";
            }

            //three special cases at 0 and 4 and 9
            //zero does nothing
            //4 and 9 use two characters
            string addedString = "";
            if (thisNum < 4) {
                for (int j = 0; j < thisNum; j++) {
                    addedString = addedString + baseString;
                }
            } else if (thisNum == 4) {
                addedString = baseString + midString;
            } else if (thisNum > 4 && thisNum < 9) {
                addedString = midString;
                for (int j = 0; j < thisNum - 5; j++) {
                    addedString = addedString + baseString;
                }
            } else if (thisNum == 9) {
                addedString = baseString + topString;
            }

            numeral = addedString + numeral;

            tenMultiplier++;
        }

        if (numeral == "") {
            numeral = "(no symbols present)";
        }

        cout << "The new numeral:" << numeral << endl;

        return 0;
    }

    //implicit isNumeral

    //if the input is a roman numeral
    //cout << "Thank you for putting in a Roman Numeral" << endl;
    string romanNumeral = number;
    int prev = -1;   //-1 == nothing (for pairing)
    int minNum = -1; //-1 == nothing (for validity)
    int sum = 0;     //our numeric representation
    for (int i = 0; i < romanNumeral.size(); i++) {
        int thisNumber = -1;
        //map the values
        thisNumber = symbolMap[romanNumeral.at(i)];

        //check for validity
        if (minNum != -1 && thisNumber > minNum * 10) {
            //this numeral is invalid
            cout << "Invalid Numeral, numerals in wrong order," << endl;
            cout << "please execute again with different argument" << endl;
            return 0;
        }
        //check for maximum number of side by side occurances (if wanted, but not needed)

        //get new minimum number
        if (minNum == -1) {
            minNum = thisNumber;
        } else if (minNum > thisNumber) {
            minNum = thisNumber;
        }

        //the subtraction and addition conditionals
        if (prev != -1 && prev < thisNumber) {
            //this is a pair (subtract)
            sum += (thisNumber - prev);
            prev = -1;
        } else {
            //the previous is not a pair (because it is decreasing) (add)
            if (prev != -1) {
                sum += prev;
            }

            if (i == romanNumeral.size() - 1) {
                //only add if we are at the end of the numeral
                sum += thisNumber;
            }

            prev = thisNumber;
        }
    }

    cout << sum << endl;
    return 0;
}
