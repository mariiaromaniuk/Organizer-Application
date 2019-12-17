//
//  gui.cpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#include "gui.hpp"

GUI::GUI(){
}

GUI::~GUI(){
}

void GUI::welcome(){
    cout << "Welcome to Organizer Application" << endl;
}

void GUI::organizer_options(){
    cout << endl;
    cout << "1) Create New Project" << endl;
    cout << "2) Select Existing Project" << endl << endl;
}

void GUI::display_organizers(vector<Organizer*> organizers){
    cout << endl << endl;
    cout << "   ";
    cout << setw(NW) << left << "ID";
    cout << setw(TW) << left << "TITLE";
    cout << setw(NW) << left << "PRIORITY";
    cout << setw(NW) << left << "TASKS";
    cout << setw(TW) << left << "DUE DATE";
    cout << endl;
    
    for (int i = 0; i < organizers.size(); ++i){
        Organizer* current = organizers[i];
        
        cout << i + 1 << ") ";
        cout << setw(NW) << left << current->id;
        cout << setw(TW) << left << current->title;
        cout << setw(NW) << left << current->priority;
        cout << setw(NW) << left << current->count;
        cout << setw(TW) << left << current->due_date << endl;
    }
    
    cout << endl << endl;
}


void GUI::task_options(){
    cout << endl << endl;
    cout << "1) Modify Project" << endl;
    cout << "2) Delete Project" << endl;
    cout << "3) Add New Task" << endl;
    cout << "4) Select Task" << endl;
    cout << "5) Back" << endl << endl;
}

void GUI::display_tasks(vector<Task*> tasks){
    cout << endl << endl;
    cout << "   ";
    cout << setw(NW) << left << "ID";
    cout << setw(TW) << left << "NAME";
    cout << setw(TW) << left << "DUE DATE";
    cout << endl;
    
    for (int i = 0; i < tasks.size(); ++i){
        Task* current = tasks[i];
        
        cout << i + 1 << ") ";
        cout << setw(NW) << left << current->id;
        cout << setw(TW) << left << current->name;
        cout << setw(TW) << left << current->date << endl;
    }
    cout << endl << endl;
}


void GUI::subtask_options(){
    cout << endl;
    cout << "1) Modify Task" << endl;
    cout << "2) Delete Task" << endl;
    cout << "3) Add New Subtask" << endl;
    cout << "4) Select Subtask" << endl;
    cout << "5) Back" << endl << endl;
}

void GUI::display_subtasks(vector<Subtask*> subtasks){
    cout << endl << endl;
    cout << "   ";
    cout << setw(NW) << left << "ID";
    cout << setw(TW) << left << "NAME";
    cout << setw(TW) << left << "DUE DATE";
    cout << endl;
    
    for (int i = 0; i < subtasks.size(); ++i){
        Subtask* current = subtasks[i];
        
        cout << i + 1 << ") ";
        cout << setw(NW) << left << current->id;
        cout << setw(TW) << left << current->name;
        cout << setw(TW) << left << current->date << endl;
    }
    cout << endl << endl;
}

void GUI::subtask_details(){
    cout << endl << endl;
    cout << "1) Modify Subtask" << endl;
    cout << "2) Delete Subtask" << endl;
    cout << "3) Back" << endl << endl;
}

void GUI::error(const int& choice, Organizer* organizer, Task* task, Subtask* subtask){
    cerr << endl << endl;
    cerr << "## ERROR: Failed to ";
    
    switch (choice){
        case GUI_CREATE:
            cerr << "create: ";
            break;
        case GUI_MODIFY:
            cerr << "modify: ";
            break;
        case GUI_DELETE:
            cerr << "delete: ";
            break;
    }
    
    if (organizer)
        cerr << organizer->title;
    else if (task)
        cerr << task->name;
    else if (subtask)
        cerr << "#" << subtask->id << " at " << subtask->date;
    
    cerr << " !" << endl;
    cerr << endl << endl;
}
