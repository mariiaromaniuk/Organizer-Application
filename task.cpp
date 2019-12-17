//
//  task.cpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#include "task.hpp"

Task::Task(){
    id = "";
    name = "";
    date = "";
}

Task::Task(string id, string name, string date){
    this->id = id;
    this->name = name;
    this->date = date;
}

Task::~Task(){
}
