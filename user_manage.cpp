#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> get_users(){
    vector<string> users;
    //Command to display all of the users in the system and store in temp.txt
    string getUserCmd = "getent passwd {1000..6000} | cut -d: -f1 /etc/passwd > temp.txt";
    system(getUserCmd.c_str());

    //Open temp.txt and read line by line the users in the system and store in an array for printing to the screen to give users options to choose from
    string line;
    ifstream myfile ("temp.txt");
    if(myfile.is_open()){
        while(getline(myfile, line)){
            users.push_back(line);
        }
    ofstream myfile;
    }else{
        cout << "Problem opening file temp.txt! \n Exiting program";
    }

    return users;
}

void add_user(){
    string UID;
    string group;

    //Get username from the sys admin
    string userName;
    cout << "Enter the username for the new user" << endl;
    cin >> userName;

    //Determine if sys admin wants to create a home directory for this user
    char createHome;
    cout << "Do you want to create a home directory for the user? [Y/N]" << endl;
    cin >> createHome;

    //Determine if sys admin wants to give a specific UID for the new user or not
    char specificUID;
    cout << "Do you want to use a specific UID for the new user? [Y/N]" << endl;
    cin >> specificUID;

    if(specificUID == 'y' || specificUID == 'Y'){
        cout << "Enter the UID for the user" << endl;
        cin >> UID;
    }

    //Determine if sys admin wants to add new user to a specific group or not
    char specificGroup;
    cout << "Do you want to add the new user to an existing group? [Y/N]" << endl;
    cin >> specificGroup;

    if(specificGroup == 'y' || specificGroup == 'Y'){
        cout << "Enter the group name to add the user to" << endl;
        cin >> group;
    }

    //Build the command to pass to the system
    string addUserCmd = "sudo useradd";

    //If sys admin wants to add a home directory include that option in the addUserCmd string
    if(createHome == 'y' || createHome == 'Y'){
        addUserCmd += " -m";
    }

    if(specificUID == 'y' || specificUID == 'Y'){
        addUserCmd += " -u " + UID;
    }

    if(specificGroup == 'y' || specificGroup == 'Y'){
        addUserCmd += " -g " + group;
    }

    addUserCmd += " " + userName;

    //Make system call to actually add an user
    system(addUserCmd.c_str());

    cout << "New user successfully created!" << endl;

    cout << "Now we will enter a password for: " + userName << endl;
    string addPass = "sudo passwd " + userName;
    system(addPass.c_str());

    return;
}

//Helper method to print all users stored in the vector u
void print_users(vector<string> u){
    cout << "Current users in the system: " << endl;
    int j = 0;
    for(auto i = u.begin(); i != u.end(); ++i){
        cout << j << ": " << *i << endl;
        j++;
    }
}

void del_user(){
    //Vector to store all of the users currently in the system
    vector<string> users;
    users = get_users();

    //Print out the current users in the system for the sys admin to choose from
    print_users(users);

    char choice;
    cout << "Enter the number associated with the user you want to delete" << endl;
    cin >> choice;

    //Convert number to an int for use
    int index = choice - 4;
    //Username of the user to remove
    string userToDel = users.at(index - 1);
    cin.ignore();

    //Call deluser command on the user the sys admin selected
    string delUserCmd = "sudo deluser";
    delUserCmd += " " + userToDel;
    system(delUserCmd.c_str());

    cout << "User successfully deleted" << endl;
    return;
}

void lock_user(string u){
    string lockCmd = "sudo usermod -L " + u;
    system(lockCmd.c_str());
    return;
}

void unlock_user(string u){
    string unlockCmd = "sudo usermod -U " + u;
    system(unlockCmd.c_str());
    return;
}

void rename_user(string u){
    string newName;
    cout << "Please enter the new name for the the user: " << u << endl;
    cin >> newName;

    string renameCmd = "sudo usermod -l " + newName + u;
    system(renameCmd.c_str());
    return;
}

void change_expiry(string u){
    string expiry;
    cout << "Please enter the expiry date in YYYY-MM-DD format:" << endl;
    cin >> expiry;

    string expiryCmd = "sudo usermod -e " + expiry + " " + u;
    system(expiryCmd.c_str());
    return;
}

void change_home(string u){
    string newHome;
    cout << "Please enter the new home directory for " << u << ":" << endl;
    cin >> newHome;

    string homeCmd = "sudo usermod -d " + newHome + " " + u;
    system(homeCmd.c_str());
    return;
}

void mod_user(){
    //Vector to store all of the users currently in the system
    vector<string> users;
    users = get_users();

    //Print out the current users in the system for the sys admin to choose from
    print_users(users);

    char choice;
    cout << "Enter the number associated with the user you want to modify" << endl;
    cin >> choice;

    //Convert number to an int for use
    int index = choice - 4;
    //Username of the user to remove
    string userToMod = users.at(index - 1);
    cin.ignore();


    //Ask them what they would like to do
    char option;
    cout << "Enter [L/l] to lock the user" << endl;
    cout << "Enter [U/u] to unlock the user" << endl;
    cout << "Enter [N/n] to change the user's name" << endl;
    cout << "Enter [E/e] to set expiry date" << endl;
    cout << "Enter [H/h] to change the user's home directory" << endl;

    cout << "Enter an option:" << endl;
    cin >> option;
    
    switch(option){
        //Call add user function
        case 'L':
        case 'l':
            lock_user(userToMod);
            break;
        //Call delete user function
        case 'U':
        case 'u':
            unlock_user(userToMod);
            break;
        //Call modify user function
        case 'N':
        case 'n':
            rename_user(userToMod);
            break;
        case 'E':
        case 'e':
            change_expiry(userToMod);
            break;
        case 'H':
        case 'h':
            change_home(userToMod);
            break;
        default:
            return;
    }      

}

void user_manage(){
    char option;
    cout << "Enter [A/a] to add a new user" << endl;
    cout << "Enter [D/d] to delete a user" << endl;
    cout << "Enter [M/m] to modify a user" << endl;
    cout << "Enter [C/c] to cancel and go back" << endl;

    cout << "Enter an option:" << endl;
    cin >> option;
    
    switch(option){
        //Call add user function
        case 'A':
        case 'a':
            add_user();
            break;
        //Call delete user function
        case 'D':
        case 'd':
            del_user();
            break;
        //Call modify user function
        case 'M':
        case 'm':
            mod_user();
            break;
        case 'C':
        case 'c':
            return;
        default:
            return;
    }      
}