#pragma once
#include <string>
#include <vector>
using namespace std;

#include "Order.h"
#include "Customer.h"

class Action;
class Volunteer;

// Warehouse responsible for Volunteers, Customers and Actions.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        void start();
        const vector<Action*> &getActions() const;
        void addOrder(Order* order);
        void addAction(Action* action);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<Customer*> &getCustomers() const;
        int getOrderCounter() const;
        void close();
        void open();
        void addCustomer(Customer* _customer);
        int getCustomerCounter() const;

    private:
        bool isOpen;
        vector<Action*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers; 
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        void parseConfigFile(const string &configFilePath);
        void IdentifyAndPreform(std::string &syntax);
        int getFirstNumber(const std::string& input);
        string extractStringAfterSpaces(const std::string& input, int spaces);
        int orderCounter;
};
