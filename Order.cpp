#include "../include/Order.h"


Order::Order (int id, int customerId, int distance):
id(id), customerId(customerId), distance(distance), status((OrderStatus)NO_VOLUNTEER), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER){};

int Order::getId() const{
    return id;
}

int Order:: getCustomerId() const{
    return customerId;
}

int Order:: getDistance() const {
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
    return "the id of the order is" +std::to_string(getId())+ ","+ "customer id:" + std::to_string(getCustomerId())+ "," + "status order:" + getStatus()+ "collector id:" + std::to_string(getCollectorId())+ "," + "driver id:" + std::to_string(getDriverId());
}
