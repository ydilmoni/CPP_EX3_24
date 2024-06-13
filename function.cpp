#include <iostream>

using namespace std;

std::string operator*(int n, const std::string &s)
{
    std::string result;
    for (int i = 0; i < n; ++i)
    {
        result += s;
    }
    return result;
}

void printds()
{
    int size = 3, firstPading = size * 5 + 1, middlePading = size * 4, insidePadding = 0, num = 1;
    string space = "  ", star = "*";
    string firstStar = firstPading * space + star;
    string rightStar = insidePadding * space + star;
    string leftStar = middlePading * space + star;

    // cout << (firstPading)*space + star + (middlePading + 1) * space + star + (middlePading + 1) * space + star << endl;
    while (middlePading >= 0)
    {
        firstStar = firstPading * space + star;
        rightStar = insidePadding * space + star;
        leftStar = middlePading * space + star;
        firstPading -= 1;
        middlePading -= 2;
        insidePadding += 2;
        cout << firstStar + rightStar + leftStar + rightStar + leftStar + rightStar << endl;
    }
    cout << firstStar + rightStar + leftStar + rightStar + leftStar + rightStar << endl;
    cout << firstStar + rightStar + leftStar + rightStar + leftStar + rightStar << endl;
    cout << firstStar + rightStar + leftStar + rightStar + leftStar + rightStar << endl;

    // firstPading -= 1;
    middlePading = 1;
    insidePadding -= 2;
    firstStar = firstPading * space + star;
        rightStar = insidePadding * space + star;
        leftStar = middlePading * space + star;
    
    cout << firstStar + rightStar + leftStar + rightStar + leftStar + rightStar << endl;
}