//
//  subtask.cpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#include "subtask.hpp"

Subtask::Subtask(){
    id = "";
    name = "";
    date = "";
}

Subtask::Subtask(string id, string name, string date){
    this->id = id;
    this->name = name;
    this->date = date;
}

Subtask::~Subtask(){
}
