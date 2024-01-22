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



WareHouse:: WareHouse(const string &configFile): isOpen(false),customerCounter(0),volunteerCounter(0),orderCounter(0){
    pendingOrders = {};
    inProcessOrders = {};
    completedOrders = {};
    parseConfigFile(configFile);
}
void WareHouse::start(){
    open();
    std::string action;
    std::cout << "Warehouse is open!" << std::endl;
    std:cout << "Please enter a Legal Action" << std::endl;
    std::getline(std::cin,action);
    while(action!="close")
    {
        IdentifyAndPreform(action);
        std::cout << "Please enter a Legal Action" << std::endl;
        std::getline(std::cin,action);
    }
    Close* closeCommand=new Close();
    closeCommand->act(*this);
    addAction(closeCommand);
}
const vector<Action*>& WareHouse::getActions() const{
    return actionsLog;
}
void WareHouse:: addOrder(Order* order){
    pendingOrders.push_back(order);
    orderCounter=orderCounter++;
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
    
}
Volunteer& WareHouse:: getVolunteer(int volunteerId) const{
    for(Volunteer* volunteer :volunteers){
        if(volunteer->getId()==volunteerId){
            return *volunteer ;
        }
    }
    CollectorVolunteer* notExist=new CollectorVolunteer(-1,"notExist",-1);
    return *notExist;
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
}
const vector<Customer*>& WareHouse:: getCustomers() const{
    return customers;
}
int WareHouse:: getOrderCounter() const{
    return orderCounter;
}
void WareHouse::close(){
isOpen=false;
}
void WareHouse::open(){
    isOpen=true;
}

void WareHouse::addCustomer(Customer* _customer){
    customers.push_back(_customer);
    customerCounter++;
} 

int WareHouse::getCustomerCounter() const{
    return customerCounter;
}


void WareHouse:: IdentifyAndPreform(std::string &syntax) {
    int input=getFirstNumber(syntax);
    if(syntax[0]=='s'){
     SimulateStep* steps = new SimulateStep (input);
     steps->act(*this);
     addAction(steps);
    }
    else if (syntax[0]=='v')
    {
       PrintVolunteerStatus* statusPrint = new PrintVolunteerStatus(input);
       statusPrint->act(*this);
      addAction(statusPrint);
    }
    else if (syntax[0]=='l')
    {
         PrintActionsLog* logs;
         logs->act(*this);
         addAction(logs);
         
    }
    else if (syntax[0]=='b')
    {
        BackupWareHouse* backup;
        backup->act(*this);
        addAction(backup);
    }
    else if (syntax[0]=='r')
    {
         RestoreWareHouse* restore;
         restore->act(*this);
         addAction(restore);
    }
    else if (syntax[0]=='o')
    {
        if(syntax[5]=='s'){
             PrintOrderStatus* _order=new PrintOrderStatus(input);
             _order->act(*this);
             addAction(_order);
             
        }
        else{
             AddOrder* orderAction=new AddOrder(input);
             orderAction->act(*this);
             addAction(orderAction);
        }
    }
    else{
        if (syntax[8]=='s')
        {
             PrintCustomerStatus* costumerStatus= new PrintCustomerStatus(input);
             costumerStatus->act(*this);
             addAction(costumerStatus);
        }
        else{
            string name=extractStringAfterSpaces(syntax,1);
            string role=extractStringAfterSpaces(syntax,2);
            string newDistancestr= extractStringAfterSpaces(syntax,3);
            string maxOrderstr= extractStringAfterSpaces(syntax,4);
            int newDistanceint = std::stoi( newDistancestr);
            int maxOrderint = std::stoi( maxOrderstr);
            AddCustomer* addCus =new AddCustomer(name,role,newDistanceint,maxOrderint);
            addCus->act(*this);
            addAction(addCus);
        }
        
        
    }   
}
int WareHouse:: getFirstNumber(const std::string& input) {
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
string WareHouse:: extractStringAfterSpaces(const std::string& input, int spaces) {
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

            Customer *_newCustomer = nullptr;
            if (customerType == "soldier") {
                _newCustomer = new SoldierCustomer(customerCounter, name, distance, maxOrders);

            } else if (customerType == "civilian") {
                _newCustomer = new CivilianCustomer(customerCounter, name, distance, maxOrders);

            }
            customerCounter=customerCounter++;
           customers.push_back(_newCustomer);
            
        } else if (type == "volunteer") {
            string name, role;
            Volunteer *newVolunteer = nullptr;
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
            if (role == "limited_collector") {
                newVolunteer = new LimitedCollectorVolunteer(volunteerCounter, name, cooldown, maxOrders);
            } else if (role == "limited_driver") {
                newVolunteer = new LimitedDriverVolunteer(volunteerCounter, name, maxDistance, distancePerStep, maxOrders);
            } else if (role == "collector") {
                newVolunteer = new CollectorVolunteer(volunteerCounter, name, cooldown);
            } else if (role == "driver") {
                newVolunteer = new DriverVolunteer(volunteerCounter, name, maxDistance, distancePerStep);
            }
            volunteerCounter=volunteerCounter++;
            volunteers.push_back(newVolunteer);
    }
    configFile.close();
}

}
