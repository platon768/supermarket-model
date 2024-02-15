#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int MIN_ARRIVAL_RATE = 10;
const int MAX_ARRIVAL_RATE = 40;
const int MIN_SHOPPING_TIME = 12;
const int MAX_SHOPPING_TIME = 25;
const int CASHIER_TIME = 3;
const int NUM_CASHIER = 4;
const int NUM_HOURS = 8;

class Customer {
private:
    int shoppingTime;
public:
    Customer() {
        shoppingTime = rand() % (MAX_SHOPPING_TIME - 9) + MIN_SHOPPING_TIME;
    }

    int getShoppingTime() {
        return shoppingTime;
    }
};

class Cashier {
private:
    bool busy;
    int remainingTime;
public:
    Cashier() {
        busy = false;
        remainingTime = 0;
    }

    bool isBusy() {
        return busy;
    }

    void startTransaction(int time) {
        busy = true;
        remainingTime = time;
    }

    void decrementTime() {
        if (remainingTime > 0)
            remainingTime--;
        if (remainingTime == 0)
            busy = false;
    }
};

int main() {
    srand(time(NULL));

    std::vector<Cashier> cashiers(NUM_CASHIER);
    int servedCustomers = 0;
    int leftCustomers = 0;

    for (int hour = 1; hour <= NUM_HOURS; hour++) {
        int customersArriving = rand() % (MAX_ARRIVAL_RATE - 9) + MIN_ARRIVAL_RATE;

        std::cout << "Hour " << hour << ": " << customersArriving << " customers arrived." << std::endl;

        std::vector<Customer> customers(customersArriving);

        for (int time = 1; time <= 60; time++) { 
            for (int i = 0; i < customers.size(); i++) {
                if (customers[i].getShoppingTime() == time) {
                    bool served = false;
                    for (int j = 0; j < cashiers.size(); j++) {
                        if (!cashiers[j].isBusy()) {
                            cashiers[j].startTransaction(CASHIER_TIME);
                            served = true;
                            servedCustomers++;
                            break;
                        }                           
                    }                        
                    if (!served)
                        leftCustomers++;
                }
            }

            for (int i = 0; i < cashiers.size(); i++) {
                cashiers[i].decrementTime();
            }
        }
    }

    std::cout << "Served customers: " << servedCustomers << std::endl;
    std::cout << "Customers left: " << leftCustomers << std::endl;

    return 0;
}
