#include "../include/Order.h"


Order::Order (int id, int customerId, int distance):
id(id), customerId(customerId), distance(distance), status((OrderStatus)NO_VOLUNTEER), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER){};

int Order::getId() const{
    return id;
}

int Order:: getCustomerId() const{
    return customerId;
}

int Order:: getDistance() const{
    return distance;
}

void Order::setStatus(OrderStatus status){
    this -> status = status ;

}

void Order:: setCollectorId(int collectorId){
    this -> collectorId = collectorId;
}

void Order:: setDriverId(int driverId){
    this -> driverId = driverId;
}

int Order::getCollectorId() const{
    return collectorId;
}

int Order:: getDriverId() const{
    return driverId;
}

OrderStatus Order:: getStatus() const{
    return status;
}

const string Order:: toString() const{
    return "OrderId: " +std::to_string(getId())+ "\n"+"OrderStatus: "+ std::to_string(static_cast<int>(getStatus()))+"\n" +"CustomerID: " + std::to_string(getCustomerId())+ "\n" +"Collector: " + std::to_string(getCollectorId()) + "Driver: " + std::to_string(getDriverId());
}
