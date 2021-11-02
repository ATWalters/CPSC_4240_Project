#include <iostream>
#include "file_perm.cpp"

using namespace std;

int main() {
    char option;
    bool quit = false;

    do{
        cout << "Enter [F/f] for file permissions" << endl;
        cout << "Enter [U/u] for user management" << endl;
        cout << "Enter [L/l] for log management" << endl;
        cout << "Enter [Q/q] to quit program" << endl;

        cout << "Enter an option:" << endl;

        cin >> option;
        switch(option){
            //Go to the file permissions
            case 'F':
            case 'f':
                file_perm();
                break;
            //Quit the program
            case 'Q':
            case 'q':
                quit = true;
                break;
            default:
                quit = true;
                break;
        }      
    }while(!quit);
    return 0;
}