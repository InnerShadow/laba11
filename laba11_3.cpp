#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

bool find_gt(list<char> lst, char value){
    list<char>::iterator p = lst.begin();
    while (p != lst.end()){
        if(*p == value){
            return true;
        }
        ++p;
    }
    return false;
}

void Print2_4(list<char> lst){
    list<char>::iterator p = lst.begin();
    while (p != lst.end()){
        cout << *p << " ";
        ++p;
    }
    cout << endl;
}

void choosing(list<char> list1, list<char> list2){
    list<char> newlist;

    for(auto p: list1){
        list<char>::iterator pos2 = find(list2.begin(), list2.end(), p);
        list<char>::iterator newpos = find(newlist.begin(), newlist.end(), p);
        cout << "pos2 = " << int(*pos2) << " new pos = " << int(*newpos) << endl;
        if(pos2 == list2.end() && newpos == newlist.end()){
            cout << ":::" << p << " " << endl;
            newlist.push_back(p);
        }
    }

    Print2_4(newlist);
}

void laba2_4(){
    //
    // TODO: вкорячить в это задание для поиска элементов функцию std::find()
    //
    list<char> firstlist;
    cout << "Enter number of elements of first list: ";
    int size = 0;
    cin >> size;
    for(int i = 0; i < size; i++){
        char value = '0';
        cin >> value;
        firstlist.push_back(value);
    }
    list<char> second;
    cout << "Enter number of elements of second list: ";
    cin >> size;
    for(int i = 0; i < size; i++){
        char value = '0';
        cin >> value;
        second.push_back(value);
    }
    choosing(firstlist, second);
}

double getSum(list<int> head, int n){
    list<int> cpy(head);
    list<int>::iterator p = head.begin();
    list<int>::reverse_iterator rp = cpy.rbegin();
    int i = 0;
    int sum = 0;
    while (i < n){
        sum += *p + *rp;
        ++p;
        ++rp;
        i++;
    }
    return sum;
}

void laba2_6(){
    int n = 0;
    cout << "Enter n: ";
    cin >> n;
    list<int> head;
    for(int i = 0; i < 2 * n; i++){
        double value = 0;
        cin >> value;
        head.push_back(value);
    }
    double sum = 0;
    int actualN = 0;
    sum = getSum(head, n);
    cout << sum;
}

int main(){
    int key = 0;
    cout << "Enter 4 if u want task 2_4 and 6 for 2_6: ";
    cin >> key;
    switch(key){
        case 4 :{
            laba2_4();
            break;
        }
        case 6 :{
            laba2_6();
            break;
        }
        default:{
            cout << "Try to read!";
            return 0;
        }
    }
    return 0;
}