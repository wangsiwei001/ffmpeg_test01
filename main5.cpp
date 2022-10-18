//
// Created by 10593 on 2022/10/18.
//
#include "string"
#include <iostream>
using namespace std;
int main(){
    char aa = '1112';
    char *cc = &aa;
    int a = 0;
    int b = 2;
    int c = 0;
    for (int i = 0; i < 4; ++i) {
//        a = (a << 8)| cc[i];
        cout << cc[i] << endl;
//        cout << a << endl;
    }
    return 0;
}