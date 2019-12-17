//
//  database_handler.cpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#include "database_handler.hpp"

DatabaseHandler::DatabaseHandler(){
    db = nullptr;
    filename = "";
}

DatabaseHandler::DatabaseHandler(string filename){
    this->filename = filename;
    this->open_db();
}

DatabaseHandler::~DatabaseHandler(){
    sqlite3_close(db);
}

bool DatabaseHandler::open_db(){
    int rc = sqlite3_open(filename.c_str(), &db);
    if (rc) return false;
    
    string sql = "SELECT * FROM organizers;";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    
    if (rc)
        if(!create_main_organizer_table())
            return false;
    return true;
}

bool DatabaseHandler::create_main_organizer_table(){
    if (!db) return false;
    
    string sql = SQL::create_organizer_main_table();
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    
    if (rc)
        return false;
    return true;
}

bool DatabaseHandler::perform_action(const int& action, Organizer* organizer, Task* task, Subtask* subtask){
    if (!db) return false;
    string sql;
    
    bool is_organizer = organizer && !task && !subtask;
    bool is_task = organizer && task && !subtask;
    bool is_subtask = organizer && task && subtask;
    
    switch (action){
        case DATABASE_CREATE:
            if (is_organizer){
                sql = SQL::create_organizer(organizer);
            } else if (is_task){
                sql = SQL::create_task(task, organizer);
            } else if (is_subtask){
                sql = SQL::create_subtask(subtask, task, organizer);
            }
            
            break;
            
        case DATABASE_MODIFY:
            if (is_organizer){
                sql = SQL::modify_organizer(organizer);
            } else if (is_task){
                sql = SQL::modify_task(task, organizer);
            } else if (is_subtask){
                sql = SQL::modify_subtask(subtask, task, organizer);
            }
            
            break;
            
        case DATABASE_REMOVE:
            if (is_organizer){
                sql = SQL::remove_organizer(organizer);
            } else if (is_task){
                sql = SQL::remove_task(task, organizer);
            } else if (is_subtask){
                sql = SQL::remove_subtask(subtask, task, organizer);
            }
            break;
            
        default:
            cerr << "wrong constant" << endl;
            return false;
    }
    
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc){
        cerr << "Failed command" << endl;
        return false;
    }
    return true;
}


vector<Organizer*> DatabaseHandler::get_all_organizers(){
    string id, title, priority, count, due_date;
    string sql = "SELECT * FROM organizers;";
    sqlite3_stmt* st = nullptr;
    vector<Organizer*> vfund;
    
    int rc = sqlite3_prepare_v3(db, sql.c_str(), sql.size(), 0, &st, nullptr);
    
    if (rc != SQLITE_OK) return vfund;
    
    while(true){
        rc = sqlite3_step(st);
        if (rc != SQLITE_ROW) break;
        
        id = (const char*)sqlite3_column_text(st, 0);
        title = (const char*)sqlite3_column_text(st, 1);
        priority = (const char*)sqlite3_column_text(st, 2);
        count = (const char*)sqlite3_column_text(st, 3);
        due_date = (const char*)sqlite3_column_text(st, 4);
        
        Organizer* organizer = new Organizer(id, title, priority, count, due_date);
        vfund.push_back(organizer);
    }
    sqlite3_finalize(st);
    
    return vfund;
}

vector<Task*> DatabaseHandler::get_all_tasks(Organizer* organizer){
    string id, name, date;
    string sql = "SELECT * FROM tasks_";
    sql += organizer->id;
    sql += ";";
    sqlite3_stmt* st = nullptr;
    vector<Task*> vtask;
    
    int rc = sqlite3_prepare_v3(db, sql.c_str(), sql.size(), 0, &st, nullptr);
    if (rc != SQLITE_OK) return vtask;
    
    while(true){
        rc = sqlite3_step(st);
        if (rc != SQLITE_ROW) break;
        
        id = (const char*)sqlite3_column_text(st, 0);
        name = (const char*)sqlite3_column_text(st, 1);
        date = (const char*)sqlite3_column_text(st, 2);
        
        Task* task = new Task(id, name, date);
        vtask.push_back(task);
    }
    
    sqlite3_finalize(st);
    
    return vtask;
}

vector<Subtask*> DatabaseHandler::get_all_subtasks(Task* task, Organizer* organizer){
    string id, name, date;
    string sql = "SELECT * FROM subtasks_";
    sql += task->id;
    sql += "_";
    sql += organizer->id;
    sql += ";";
    sqlite3_stmt* st = nullptr;
    vector<Subtask*> vpay;
    
    int rc = sqlite3_prepare_v3(db, sql.c_str(), sql.size(), 0, &st, nullptr);
    if (rc != SQLITE_OK) return vpay;
    
    while(true){
        rc = sqlite3_step(st);
        if (rc != SQLITE_ROW) break;
        
        id = (const char*)sqlite3_column_text(st, 0);
        name = (const char*)sqlite3_column_text(st, 1);
        date = (const char*)sqlite3_column_text(st, 2);
        
        Subtask* subtask = new Subtask(id, name, date);
        vpay.push_back(subtask);
    }
    sqlite3_finalize(st);
    
    return vpay;
}
