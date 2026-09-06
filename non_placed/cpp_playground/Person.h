//
// Created by rgoncalo on 03/09/2026.
//

#ifndef CPP_PLAYGROUND_PERSON_H // if was not yet defined
#define CPP_PLAYGROUND_PERSON_H //define it

// #pragma once could be used to include this file only one time

#include <string>

class Person {

private:
    std::string name;

public:
    Person(std::string name);
    std::string getName();


};

#endif //CPP_PLAYGROUND_PERSON_H
