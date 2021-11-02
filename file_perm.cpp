#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

string questions(string);

void file_perm(){
    string filePath;
    string newPerms = "chmod ";
    string temp;

    cout << "Please enter the file path of the file to change" << endl;
    cin >> filePath;

    newPerms += questions("owners");
    newPerms += questions("group");
    newPerms += questions("world");

    newPerms = newPerms + " " + filePath;
    system(newPerms.c_str());
    cout << "File permissions changed for file: " << filePath << endl;
}

string questions(string s){

    int perms = 0;
    char choice;
    cout << "Would you like " << s <<  " to have execute permissions? [y/n]" << endl;
    cin >> choice;
    if(choice == 'y' || choice == 'Y'){
        perms += 1;
    }

    cout << "Would you like " << s <<  " to have write permissions? [y/n]" << endl;
    cin >> choice;
    if(choice == 'y' || choice == 'Y'){
        perms += 2;
    }

    cout << "Would you like " << s <<  " to have read permissions? [y/n]" << endl;
    cin >> choice;
    if(choice == 'y' || choice == 'Y'){
        perms += 4;
    }

    string res = to_string(perms);
    return res;
}