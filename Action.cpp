#include "../include/Action.h"
#include <iostream>

Action:: Action(){
}
ActionStatus Action:: getStatus() const{
     return status;
}
void Action:: complete(){
status=ActionStatus::COMPLETED;
}
void Action:: error(string errorMsg){
 this -> errorMsg=errorMsg;
 std::cout << getErrorMsg() << std::endl;
 status=ActionStatus::ERROR;
}
string Action:: getErrorMsg() const{
    return errorMsg;
}
AddOrder::AddOrder(int id): customerId(id){
}

void AddOrder::act(WareHouse &wareHouse){
    vector<Customer*> myCustomers = wareHouse.getCustomers();
    bool isAdded=false;
    for(vector<Customer*>::iterator it = myCustomers.begin(); it != myCustomers.end()&&isAdded==false; ++it){
        if((*it)->getId()==customerId){
            if((*it)->canMakeOrder()==false){
                error("Cannot place this order");
            }
            else{
                Order* newOrder=new Order(wareHouse.getOrderCounter(),customerId,(*it)->getCustomerDistance());
                wareHouse.addOrder(newOrder);
                isAdded=true;
            }
        }
    }
    if(isAdded==false){
        error("Cannot place this order");
    }
    else{
        complete();
    }
}
AddOrder* AddOrder::clone() const{
    return new AddOrder(*this);
}
string AddOrder:: toString() const{
    return "Order "+std::to_string(customerId)+" "+std::to_string(static_cast<int>(getStatus()));
}

AddCustomer::AddCustomer(const string& customerName, const string& customerType, int distance, int maxOrders):customerName(customerName),distance(distance),maxOrders(maxOrders),customerType((customerType=="civilian")?CustomerType::Civilian:CustomerType::Soldier) {
}
void AddCustomer:: act(WareHouse &wareHouse){
    if(customerType==CustomerType::Soldier){
        SoldierCustomer* newSoldier=new SoldierCustomer(wareHouse.getCustomerCounter(),customerName,distance,maxOrders);
        wareHouse.addCustomer(newSoldier); 
    }
    else{
        CivilianCustomer* newCivilian=new CivilianCustomer(wareHouse.getCustomerCounter(),customerName,distance,maxOrders);
        wareHouse.addCustomer(newCivilian); 
    }
    complete();
}
AddCustomer* AddCustomer:: clone() const{
    return new AddCustomer(*this);
}
string AddCustomer:: toString() const{
    return "Customer "+customerName+" "+std::to_string(static_cast<int>(customerType))+" "+std::to_string(distance)+" "+std::to_string(maxOrders)+" "+std::to_string(static_cast<int>(getStatus()));  
}

PrintOrderStatus::PrintOrderStatus(int id):orderId(id){}

void PrintOrderStatus:: act(WareHouse &wareHouse){
    if(orderId>wareHouse.getOrderCounter()){
        error("ERROR: order doesn't exist");
    }
    else{
        Order& myOrder = wareHouse.getOrder(orderId);
        std::cout << myOrder.toString() << std::endl;
        complete();
 }
}

PrintOrderStatus* PrintOrderStatus::clone() const{
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus:: toString() const{
    return "";
}

PrintCustomerStatus:: PrintCustomerStatus(int customerId):customerId(customerId){}

void PrintCustomerStatus:: act(WareHouse &wareHouse){
    if(customerId>wareHouse.getCustomerCounter()){
        error("ERROR: Customer doesn't exist");
    }
    else{
        Customer& currCustomer= wareHouse.getCustomer(customerId);
        std::cout << "CustomerID: "+ currCustomer.getId() << std::endl;
        vector<int> myOrdersIds=currCustomer.getOrdersIds();
        for(vector<int>::iterator it = myOrdersIds.begin(); it != myOrdersIds.end(); ++it){
            std::cout << "OrderID: " << *it << std::endl;
            Order& myOrder = wareHouse.getOrder(*it);
            std::cout << "OrderStatus: " + std::to_string(static_cast<int>(myOrder.getStatus())) << std::endl;
        }
        std::cout << "NumOrdersLeft: " +std::to_string(currCustomer.getMaxOrders()-currCustomer.getNumOrders())  << std::endl;
        complete();
    }
}

PrintCustomerStatus* PrintCustomerStatus::clone() const{
    return new PrintCustomerStatus(*this);
}
string PrintCustomerStatus:: toString() const{
    return ""; //מה עושים פה 
}

PrintVolunteerStatus:: PrintVolunteerStatus(int id):VolunteerId(id){}

void PrintVolunteerStatus:: act(WareHouse &wareHouse){
    Volunteer& myVolunteer=wareHouse.getVolunteer(VolunteerId);
    if (myVolunteer.getId()==-1){

    }
}
