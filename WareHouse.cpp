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
#include "../include/Action.h"
#include <fstream>
#include <sstream>



WareHouse:: WareHouse(const string &configFile): isOpen(true), customerCounter(0), volunteerCounter(0){
    pendingOrders = {};
    inProcessOrders = {};
    completedOrders = {};
}
void WareHouse::start(){

}
const vector<Action*>& WareHouse::getActions() const{
    return actionsLog;
}
void WareHouse:: addOrder(Order* order){
    pendingOrders.push_back(order);
}
void WareHouse:: addAction(Action* action){
    actionsLog.push_back(action);
}
Customer& WareHouse:: getCustomer(int customerId) const{
    for(Customer* cust :customers){
        if(cust->getId()==customerId){
            return *cust ;
        }
    }
    throw std::invalid_argument("no customer with this id exict");
}
Volunteer& WareHouse:: getVolunteer(int volunteerId) const{
    for(Volunteer* volunteer :volunteers){
        if(volunteer->getId()==volunteerId){
            return *volunteer ;
        }
    }
    throw std::invalid_argument("no volenteer with this id exict");
}
Order& WareHouse::getOrder(int orderId) const{
    for(Order* _order :pendingOrders){
        if(_order->getId()==orderId){
            return *_order ;
        }
    }
    for(Order* _order :inProcessOrders){
        if(_order->getId()==orderId){
            return *_order ;
        }
    }
    for(Order* _order :completedOrders){
        if(_order->getId()==orderId){
            return *_order ;
        }
    }
    throw std::invalid_argument("no volenteer with this id exict");
}
void WareHouse::close(){

}
void WareHouse::open(){

}

Action stringIdentifier(std::string &syntax) {
    int input=getFirstNumber(syntax);
    if(syntax[0]=='s'){
       SimulateStep steps(input);
       return steps; 
    }
    else if (syntax[0]=='v')
    {
        PrintVolunteerStatus status(input);
       return status;
    }
    else if (syntax[0]=='l')
    {
         PrintActionsLog logs;
         return logs;
    }
    else if (syntax[0]=='b')
    {
        BackupWareHouse backup;
        return backup;
    }
    else if (syntax[0]=='r')
    {
         RestoreWareHouse restore;
         return restore;
    }
    else if (syntax[0]=='o')
    {
        if(syntax[5]=='s'){
             PrintOrderStatus orders(input);
             return orders;
        }
        else{
             AddOrder newOrder(input);
             return newOrder;
        }
    }
    else{
        if(syntax[4]=='e'){
            Close closeCommand;
            return closeCommand;
        }
        else if (syntax[8]=='s')
        {
             PrintCustomerStatus costumerStatus(input);
             return costumerStatus;
        }
        else{
            string name=extractStringAfterSpaces(syntax,1);
            string role=extractStringAfterSpaces(syntax,2);
            string newDistancestr= extractStringAfterSpaces(syntax,3);
            string maxOrderstr= extractStringAfterSpaces(syntax,4);
            int newDistanceint = std::stoi( newDistancestr);
            int maxOrderint = std::stoi( maxOrderstr);
            AddCustomer newCustomer(name,role,newDistanceint,maxOrderint);
            return newCustomer;
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

void WareHouse::parseConfigFile(const string &configFilePath) {
    ifstream configFile(configFilePath);
    string line;
    while (getline(configFile, line)) {
        if (line.empty() || line[0] == '#') {
            // Skip empty lines and comments
            continue;
        }

        istringstream iss(line);
        string type;
        iss >> type;

        if (type == "customer") {
            string name, customerType;
            int distance, maxOrders;
            iss >> name >> customerType >> distance >> maxOrders;

            Customer *newCustomer = nullptr;
            if (customerType == "soldier") {
                newCustomer = new SoldierCustomer(customerCounter++, name, distance, maxOrders);
            } else if (customerType == "civilian") {
                newCustomer = new CivilianCustomer(customerCounter++, name, distance, maxOrders);
            }
            customers.push_back(newCustomer);
            
        } else if (type == "volunteer") {
            string name, role;
            int cooldown, maxDistance, distancePerStep, maxOrders = -1;
            iss >> name >> role >> cooldown;

            if (role == "driver") {
                iss >> maxDistance >> distancePerStep;
            } else {
                iss >> maxDistance; // For collectors and other roles
            }

            // Check if maxOrders is provided (optional)
            if (iss >> maxOrders && maxOrders <= 0) {
                cerr << "Error: Invalid maxOrders for volunteer " << name << ". It must be greater than 0." << endl;
                continue;
            }

            Volunteer *newVolunteer = nullptr;
            if (role == "limited_collector") {
                newVolunteer = new LimitedCollectorVolunteer(volunteerCounter++, name, cooldown, maxOrders);
            } else if (role == "limited_driver") {
                newVolunteer = new LimitedDriverVolunteer(volunteerCounter++, name, maxDistance, distancePerStep, maxOrders);
            } else if (role == "collector") {
                newVolunteer = new CollectorVolunteer(volunteerCounter++, name, cooldown);
            } else if (role == "driver") {
                newVolunteer = new DriverVolunteer(volunteerCounter++, name, maxDistance, distancePerStep);
            }
            volunteers.push_back(newVolunteer);
    }
    configFile.close();
}

int main() {
    // Example usage
    std::string inputString = "fdf45gg";
    int firstNumber = getFirstNumber(inputString);

    std::cout << "The first number in the string is: " << firstNumber << std::endl;

    return 0;
}