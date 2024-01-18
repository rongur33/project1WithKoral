#pragma once
#include <string>
#include <vector>
#include <cctype>
using namespace std;
using std::string;
#include <iostream>
#include "../include/Volunteer.h"
#include "../include/Customer.h"
#include "../include/WareHouse.h"
#include "../include/BaseAction.h"

int getFirstNumber(const std::string& inputString);

WareHouse:: WareHouse(const string &configFile){

}
void stringIdentifier(string &syntax){
    int input=getFirstNumber(syntax);
    
    if(syntax[0]=='s'){
       SimulateStep steps(input);
       steps.act(); 
    }
    else if (syntax[0]=='v')
    {
        PrintVolunteerStatus status(input);
        status.act();
    }
    else if (syntax[0]=='l')
    {
         PrintActionsLog logs;
         logs.act();
    }
    else if (syntax[0]=='b')
    {
        BackupWareHouse backup;
        backup.act();
    }
    else if (syntax[0]=='r')
    {
         RestoreWareHouse restore;
         restore.act();
    }
    else if (syntax[0]=='o')
    {
        if(syntax[5]=='s'){
             PrintOrderStatus orders(input);
             orders.act();
        }
        else{
             Order newOrder(input);
             newOrder.act();
        }
    }
    else{
        if(syntax[4]=='e'){
            Close closeCommand;
            closeCommand.act();
        }
        else if (syntax[8]=='s')
        {
             PrintCustomerStatus costumerstatus(input);
             costumerstatus.act();
        }
        else{
            string name=extractStringAfterSpaces(&syntax,1);
            string role=extractStringAfterSpaces(&syntax,2);
            string newDistancestr= extractStringAfterSpaces(&syntax,3);
            string maxOrderstr= extractStringAfterSpaces(&syntax,4);
            int newDistanceint = std::stoi( newDistancestr);
            int maxOrderint = std::stoi( maxOrderstr);
            AddCustomer newCustomer(name,role,newDistanceint,maxOrderint);
            newCustomer.act();
        }
        
        
    }
    
    
    
    
    
    
}
int getFirstNumber(const std::string& input) {
    size_t i = 0;
    std::string numberStr;

    // Find the first digit in the string
    while (i < input.length() && !isdigit(input[i])) {
        ++i;
    }

    // Collect the digits to form the number
    while (i < input.length() && isdigit(input[i])) {
        numberStr += input[i];
        ++i;
         // Convert the collected digits to an integer
    int result = std::stoi(numberStr);

    return result;
}
}
std::string extractStringAfterSpaces(const std::string& input, int spaces) {
    size_t i = 0;

    // Skip the specified number of spaces
    while (i < input.length() && spaces > 0) {
        if (input[i] == ' ') {
            --spaces;
        }
        ++i;
    }

    // Find the start of the next word
    while (i < input.length() && input[i] == ' ') {
        ++i;
    }

    // Collect the letters until the next space
    std::string result;
    while (i < input.length() && input[i] != ' ') {
        result += input[i];
        ++i;
    }

    return result;
}

int main() {
    // Example usage
    std::string inputString = "fdf45gg";
    int firstNumber = getFirstNumber(inputString);

    std::cout << "The first number in the string is: " << firstNumber << std::endl;

    return 0;
}