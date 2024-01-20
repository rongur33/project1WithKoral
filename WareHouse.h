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
        void close();
        void open();

    private:
        bool isOpen;
        vector<Action*> actionsLog;//when finish parsing , build it in the constructor
        vector<Volunteer*> volunteers;//when finish parsing , build it in the constructor
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers; //when finish parsing , build it in the constructor
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
};