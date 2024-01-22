#include "../include/Customer.h"

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders):
 id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders){ordersId={};};

 const string& Customer::getName() const {
    return name;
 }

 int Customer::getCustomerDistance() const{
    return locationDistance;
 }

 int Customer:: getMaxOrders() const{
    return maxOrders;
 }

 int Customer:: getNumOrders() const{
    return ordersId.size();
 }

 bool Customer ::canMakeOrder() const{
    if(maxOrders - ordersId.size() > 0)
        return true;
    else
        return false;
 }

const vector<int>& Customer:: getOrdersIds() const{
    return ordersId;
}

int Customer:: addOrder(int orderId){
    if(canMakeOrder() == true){
        ordersId.push_back(orderId);
        return id;
    }
    return -1;
}

 SoldierCustomer::SoldierCustomer(int id, string name, int locationDistance, int maxOrders) :
 Customer(id, name, locationDistance, maxOrders){};

  SoldierCustomer* SoldierCustomer:: clone() const{
    return new SoldierCustomer(*this);
  }

  CivilianCustomer::CivilianCustomer(int id, string name, int locationDistance, int maxOrders) :
 Customer(id, name, locationDistance, maxOrders){};

 CivilianCustomer* CivilianCustomer:: clone() const{
    return new CivilianCustomer(*this);
  }

