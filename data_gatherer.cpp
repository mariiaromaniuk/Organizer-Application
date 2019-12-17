//
//  data_gatherer.cpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#include "data_gatherer.hpp"

DataGatherer::DataGatherer(){
}

DataGatherer::~DataGatherer(){
}

string DataGatherer::get_selection(const int& position, Organizer* organizer, Task* task, Subtask* subtask){
    string selection, choice;
    
    switch (position){
        case GATHERER_NONE:
            selection = "Enter your selection: ";
            break;
            
        case GATHERER_ORGANIZER:
            selection = organizer->title;
            selection += "> Enter your selection: ";
            break;
            
        case GATHERER_TASK:
            selection = organizer->title;
            selection += "> ";
            selection += task->name;
            selection += "> Enter your selection: ";
            break;
            
        case GATHERER_SUBTASK:
            selection = organizer->title;
            selection += "> ";
            selection += task->name;
            selection += "> ";
            selection += subtask->date;
            selection += "> Enter your selection: ";
            break;
            
        default:
            selection = "";
    }
    
    cout << selection;
    cin >> choice;
    
    return choice;
}

bool DataGatherer::confirm_delete(){
    cout << endl << endl;
    
    cout << "Are you sure you want to delete this record (y/n)?: ";
    string choice;
    cin >> choice;
    
    return choice == "y" || choice == "Y";
}

Organizer* DataGatherer::get_organizer_data(){
    string id, title, priority, count, due_date;
    char a[100];
    
    cout << "Enter project's data: " << endl << endl;
    cout << "ID: "; cin >> id;
    cout << "Title: "; cin.ignore(); cin.getline(a, 100); title = a;
    cout << "Priority: "; cin >> priority;
    cout << "Count of Tasks: "; cin >> count;
    cout << "Date (dd-mm-yy): "; cin >> due_date;
    
    Organizer* organizer = new Organizer(id, title, priority, count, due_date);
    
    return organizer;
}

Task* DataGatherer::get_task_data(){
    string id, name, date;
    char a[100];
    
    cout << "Enter task's data: " << endl << endl;
    cout << "ID: "; cin >> id;
    cout << "Name: "; cin.ignore(); cin.getline(a, 100); name = a;
    cout << "Due Date: "; cin >> date;
    
    Task* task = new Task(id, name, date);
    
    return task;
}

Subtask* DataGatherer::get_subtask_data(){
    string id, name, date;
    
    cout << "Enter subtask's data: " << endl << endl;
    cout << "ID: "; cin >> id;
    cout << "Name: "; cin >> name;
    cout << "Date: "; cin >> date;
    
    Subtask* subtask = new Subtask(id, name, date);
    
    return subtask;
}

