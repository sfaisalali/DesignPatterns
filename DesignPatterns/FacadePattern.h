#include "pch.h"
#include <iostream>
using namespace std;

// it is okay to do all complex stuff. but need to have an easy method to do that.
// fazad will do all the complex wiring in that.
// law of demeter. / principle of least knowledge.

class Waiter_Subsystem1
{
public:
    void writeOrder() { cout << " Waiter writes client's order\n"; }
    void sendToKitchen() { cout << " Send order to kitchen\n"; }
    void serveCustomer() { cout << " Yeeei customer is served!!!\n"; }
};
class Kitchen_Subsystem2
{
public:
    void prepareFood() { cout << " Cook food\n"; }
    void callWaiter() { cout << " Call Waiter\n"; }
    void washDishes() { cout << " Wash the dishes\n"; }
};
class Order_Facade
{
private:
    Waiter_Subsystem1 waiter;
    Kitchen_Subsystem2 kitchen;
public:
    void orderFood()
    {
        cout << "A series of interdependent calls on various subsystems:\n";
        waiter.writeOrder();
        waiter.sendToKitchen();
        kitchen.prepareFood();
        kitchen.callWaiter();
        waiter.serveCustomer();
        kitchen.washDishes();
    }
};

