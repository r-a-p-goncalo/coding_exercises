#include <iostream>
#include <vector>
#include "Person.h"
#include "device_play.h"

void printArray(int v[], int size) {

    for (int i = 0; i < size; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";

}

void printVetor(std::vector<int> v) {

    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";

}

void createAndPrintPerson() {
    std::cout << "Creating Person\n";
    Person person("Ricardo");
    std::cout<< "Person name is: " + person.getName() + "\n";
}


int main() {

    int ninitialized_v[5];

    std::cout << "Non-initialized v:\n";
    printArray(ninitialized_v, 10);

    std::vector<int> initialized_v {1, 2, 3, 4, 10};

    std::cout << "Initialized v:\n";
    printVetor(initialized_v);

    createAndPrintPerson();

    std::cout << "Device play:" + device_play();

    return 0;
}