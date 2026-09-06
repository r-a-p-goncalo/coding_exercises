//
// Created by rgoncalo on 03/09/2026.
//

#include "Person.h"

Person::Person(std::string name) {
    this->name = name;
}

std::string Person::getName() {
    return this->name;
}
