#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;
void createBackGround(string *&background){
    ifstream fs("Background.txt");
    int i = 0;
    while(fs && i < 50){
        getline(fs, background[i]);
        
        i++;
    }
    fs.close();
}


int main(){
    string* background = new string[50];
    createBackGround(background);
    for(int i = 0; i < 50; i++){
        cout << background[i] <<endl;
    }
    system("pause");
}