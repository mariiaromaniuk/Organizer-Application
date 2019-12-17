//
//  database_handler.hpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#ifndef database_handler_hpp
#define database_handler_hpp

#include <stdio.h>
#include <sqlite3.h>
#include <vector>
#include "sql.hpp"

#define DATABASE_CREATE 0
#define DATABASE_MODIFY 1
#define DATABASE_REMOVE 2


class DatabaseHandler{
public:
    
public:
    DatabaseHandler();
    DatabaseHandler(string);
    ~DatabaseHandler();
    
    bool perform_action(const int&, Organizer* = nullptr, Task* = nullptr,
                        Subtask* = nullptr);
    
    vector<Organizer*> get_all_organizers();
    vector<Task*> get_all_tasks(Organizer*);
    vector<Subtask*> get_all_subtasks(Task*, Organizer*);
    
private:
    sqlite3* db;
    string filename;
    
private:
    bool open_db();
    bool create_main_organizer_table();
};

#endif /* database_handler_hpp */
