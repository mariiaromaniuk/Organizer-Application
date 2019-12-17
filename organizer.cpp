//
//  organizer.cpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#include "organizer.hpp"

Organizer::Organizer(){
    id = "";
    title = "";
    priority = "";
    count = "";
    due_date = "";
}

Organizer::Organizer(string id, string title, string priority, string count, string end_date){
    this->id = id;
    this->title = title;
    this->priority = priority;
    this->count = count;
    this->due_date = end_date;
}

Organizer::~Organizer(){
}
