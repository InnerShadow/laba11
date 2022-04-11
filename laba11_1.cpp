#include <iostream>
#include <string>
#include <cstring>
#include <math.h>

using namespace std;

void laba4_1(){
    string str;
    string newstr;
    cout << "Enter youre string: ";
    cin.get();
    getline(cin, str);
    cin.get();
    int len = str.size();
    string tempstr(str);
    int i = 0;
    for(char ch = tempstr.at(i); i < str.size(); i++){
        int icounter = 0;
        for (int ic = 0; ic < len; ic++){
            if (str.at(ic) == ch){
                icounter++;
            }
        }
        if(icounter){
            cout << "Number of " << ch << " is " << icounter << endl;
        }
        if(icounter == 1){
            newstr += ch;
        }
    }
    cout << "Final string is " << newstr;
}

void trusfermstring(int& icounter, int& ilenght, string& str, int i, int system){
    str.clear();
    do {
        int ost = i % system; 
        i /= system;                        //char* str1 = itoa(i, str1, system);
        str += char('0' + ost);             //str = string(str1);
        ilenght++;                          //ilenght = str.size();
    } while (i > 0);
    for (int i_n = 0; i_n <= ilenght / 2; i_n++){
        if(str.at(i_n) == str.at(ilenght - i_n - 1)){
            icounter++;
        } else {
            break;
        }
    }
}

void laba4_2(){
    const int iMAX_NUM = 1e6;
    string str;
    for (int i = 0; i <= iMAX_NUM; i++){
        int lenght = 0;
        int tencounter = 0;
        trusfermstring(tencounter, lenght, str, i, 10);
        if (tencounter < lenght / 2){
            continue;
        }
        lenght = 0;
        int twocounter = 0;
        trusfermstring(twocounter, lenght, str, i, 2);
        if (twocounter >= lenght / 2){
            cout << "10ss num is " << i << "; 2ss num is " << str << endl;
        }
    }
}

void laba4_3(){
    string original;
    cin.get();
    cout << "Enter youre string ";
    getline(cin, original);
    cin.get();
    int length = original.size();
    int prev_length = 0;
    for(int icounter = 0; icounter < length; icounter++){
        // while (icounter < length && (original.at(icounter) != ' ')){ //OOP-METODA-3-18 (or any other way to use array of delimiters)
        //     icounter++;
        // }
        icounter = original.find_first_of(" ,:-", icounter + 1);
        
        int irepeat = 0;
        int iunic = 0;
        for(int i = prev_length; i <= icounter - 1; i++){
            int icount = 0;
            for (int ic = prev_length; ic <= icounter - 1; ic++){
                if (original.at(ic) == original.at(i)){
                    icount++;
                }
            }
            if (icount >= 2){
                irepeat++;
            }
            if(icount == 1){
                iunic++;
            }
        }
        if (irepeat > iunic){
            for (int i = prev_length; i <= icounter - 1; i++){
                cout << original.at(i);
            }
            cout << " ";
        }
        prev_length = icounter + 1;
    }
}

int main(){
    cout << "Ener 1 for 4.1, 2 for 4.2, 3 for 4.3: \n";
    int key = 0;
    cin >> key;
    switch(key){
        case 1:{
            laba4_1();
            break;
        }
        case 2:{
            laba4_2();
            break;
        }
        case 3:{
            laba4_3();
            break;
        }
        default:{
            cout << "Try to read!";
            return 0;
        }
    }
    return 0;
}