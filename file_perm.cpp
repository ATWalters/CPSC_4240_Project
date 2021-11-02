#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void file_perm(){
    string filePath;
    string newPerms = "chmod ";
    cout << "Please enter the file path of the file to change" << endl;
    cin >> filePath;

    newPerms + questions("owners");
    newPerms + questions("group");
    newPerms + questions("world");

    newPerms = newPerms + " " + filePath;
    system(newPerms.c_str());
}

string questions(std::string s){

    int perms = 0;
    char choice;
    cout << "Would you like " << s <<  " to have execute permissions?" << endl;
    cin >> choice;
    if(choice == 'y' || choice == 'Y'){
        perms += 1;
    }

    cout << "Would you like " << s <<  " to have write permissions?" << endl;
    cin >> choice;
    if(choice == 'y' || choice == 'Y'){
        perms += 2;
    }

    cout << "Would you like " << s <<  " to have read permissions?" << endl;
    cin >> choice;
    if(choice == 'y' || choice == 'Y'){
        perms += 4;
    }

    return to_string(perms);
}