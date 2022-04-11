#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <math.h>

using namespace std;

int getfirstNumber(const string& str, int iterator_position) {
    string newstr = "";
    bool pr = false;
    int minus = 1;
    for (int i = iterator_position; i >= 0; i--) {
        if (str.at(i) == '-') {
            minus = -1;
        }
        if (str.at(i) > '9' || str.at(i) < '0') {
            if (pr) {
                break;
            }
            continue;
        }
        else {
            newstr.push_back(str.at(i));
            pr = true;
        }
    }
    reverse(newstr.begin(), newstr.end());
    int num = atoi(newstr.c_str());
    return num * minus;
}

int getsecondNumber(const string& str, int iterator_position) {
    string newstr = "";
    bool pr = false;
    int minus = 1;
    for (int i = iterator_position; i < str.size(); i++) {
        if (str.at(i) == '-') {
            minus = -1;
        }
        if (str.at(i) > '9' || str.at(i) < '0') {
            if (pr) {
                break;
            }
            continue;
        }
        else {
            newstr.push_back(str.at(i));
            pr = true;
        }
    }
    int num = atoi(newstr.c_str());
    return num * minus;
}

void coppypaster(string& str, const string& tempstr, int resualt, int& i, bool b = false) {
    str.clear();
    if (!b && tempstr.find(' ', i - 3 - int(log10(resualt + 1))) < 1024) {
        str.append(tempstr, 0, tempstr.find(' ', i - 3));
    }
    if (str.size()) {
        str += " ";
    }
    str += to_string(resualt);
    if (tempstr.find(' ', i + 2) > tempstr.size()) {
        return;                                                         // replase 2 + 2 on 4
    }
    str.append(tempstr, tempstr.find(' ', i + 2), tempstr.size() - tempstr.find(' ', i + 2));
    i = 0;
    cout << str << endl;
}

string domath(string str, string tempstr, int& resualt) {
    int first = 0;
    int second = 0;
    do {
        tempstr = str;
        int iposition = str.find('~');
        if (iposition < str.size()) {
            second = getsecondNumber(str, iposition);
            resualt = ~second;
            coppypaster(str, tempstr, resualt, iposition);
            continue;
        }
        iposition = str.find(">>");
        if (iposition < str.size()) {
            iposition++;
            first = getfirstNumber(str, iposition);
            second = getsecondNumber(str, iposition);
            resualt = first >> second;
            coppypaster(str, tempstr, resualt, iposition, 1);
            continue;
        }
        iposition = str.find("<<");
        if (iposition < str.size()) {
            iposition++;
            first = getfirstNumber(str, iposition);
            second = getsecondNumber(str, iposition);
            resualt = first << second;
            coppypaster(str, tempstr, resualt, iposition, 1);
            continue;
        }
        iposition = str.find('&');
        if (iposition < str.size()) {
            first = getfirstNumber(str, iposition);
            second = getsecondNumber(str, iposition);
            resualt = first & second;
            coppypaster(str, tempstr, resualt, iposition);
            continue;
        }
        iposition = str.find('^');
        if (iposition < str.size()) {
            first = getfirstNumber(str, iposition);
            second = getsecondNumber(str, iposition);
            resualt = first ^ second;
            coppypaster(str, tempstr, resualt, iposition);
            continue;
        }
        iposition = str.find('|');
        if (iposition < str.size()) {
            first = getfirstNumber(str, iposition);
            second = getsecondNumber(str, iposition);
            resualt = first | second;
            coppypaster(str, tempstr, resualt, iposition);
            continue;
        }
        iposition = str.find('*');
        if (iposition < str.size()) {
            first = getfirstNumber(str, iposition);
            second = getsecondNumber(str, iposition);
            resualt = first * second;
            coppypaster(str, tempstr, resualt, iposition);
            continue;
            int a;
        }
        iposition = str.find('+');
        if (iposition < str.size()) {
            first = getfirstNumber(str, iposition);
            second = getsecondNumber(str, iposition);
            resualt = first + second;
            coppypaster(str, tempstr, resualt, iposition);
            continue;
        }
    } while (str.compare(tempstr));
    return str;
}

int complitstring(string str, int begin, int end) {
    int resualt = 0;
    string newstr;
    newstr.append(str, begin + 1, end - begin - 1);  // inside breckets 
    string tempstr;
    newstr = domath(newstr, tempstr, resualt);
    return atoi(newstr.c_str());
}

void complitstring(string& str) {
    int resualt = 0;
    string tempstr;                     // final string work
    str = domath(str, tempstr, resualt);
}

string removebrackets(string str) {
    string newstr;
    int leftbreket = str.rfind('(');
    int rightbreket = str.find(')');
    if (leftbreket > rightbreket) {
        for (int i = rightbreket; i >= 0; i--) {   // (1 + (2 + 3))
            if (str.at(i) == '(') {
                leftbreket = i;
                break;
            }
        }
    }
    if (leftbreket > str.size() || rightbreket > str.size()) {
        return str;
    }
    int resualt = complitstring(str, leftbreket, rightbreket);
    newstr.append(str, 0, leftbreket);
    newstr += to_string(resualt);
    newstr.append(str, rightbreket + 1, str.size() - rightbreket + 1);
    return newstr;
}

int main() {
    string str;
    getline(cin, str);
    cin.get();
    string tempstr;
    do {
        tempstr = str;
        str = removebrackets(str);
        cout << str << endl;
    } while (str.compare(tempstr));

    complitstring(str);
    cout << str;

    return 0;
}