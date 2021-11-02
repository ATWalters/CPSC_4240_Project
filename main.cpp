#include <iostream>
#include "file_perm.cpp"

int main() {
    char option;

    do{
        std::cout << "Enter F for file permissions" << std::endl;
        std::cout << "Enter U for user management" << std::endl;
        std::cout << "Enter L for log management" << std::endl;

        std::cout << "Enter an option below:" << std::endl;

        std::cin >> option;
        switch(option){
            case 'F':
                file_perm();
            break;

            default:
            break;
        }      
    }while(option != 'q' || option != 'Q');
    return 0;
}