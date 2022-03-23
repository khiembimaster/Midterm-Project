#include <windows.h>
#include <iostream>
using namespace std;

int main(){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    for(int i = 0; i < 100; i++){
        SetConsoleTextAttribute(hStdout, i);
        Position.X = 1;
        Position.Y = 1;
	    SetConsoleCursorPosition(hStdout, Position);
        cout << i << " ";
    }


    

    
    system("pause");
}