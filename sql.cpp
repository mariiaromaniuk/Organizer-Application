//
//  sql.cpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#include "sql.hpp"

string SQL::create_organizer_main_table(){
    string script = "CREATE TABLE organizers (";
    script += "ID TEXT PRIMARY KEY NOT NULL UNIQUE, ";
    script += "Title TEXT NOT NULL, ";
    script += "Priority TEXT NOT NULL, ";
    script += "Count TEXT NOT NULL, ";
    script += "Due_Date TEXT NOT NULL);";
    
    return script;
}

string SQL::create_organizer(Organizer* organizer){
    string script = "INSERT INTO organizers VALUES('";
    script += organizer->id;
    script += "', '";
    script += organizer->title;
    script += "', '";
    script += organizer->priority;
    script += "', '";
    script += organizer->count;
    script += "', '";
    script += organizer->due_date;
    script += "'); ";
    
    script += "CREATE TABLE tasks_";
    script += organizer->id;
    script += "(ID TEXT PRIMARY KEY NOT NULL UNIQUE, ";
    script += "Name TEXT NOT NULL, ";
    script += "Date TEXT NOT NULL);";
    
    return script;
}

string SQL::modify_organizer(Organizer* organizer){
    string script = "UPDATE organizers SET ";
    script += "Title = '";
    script += organizer->title;
    script += "', Priority = '";
    script += organizer->priority;
    script += "', Count = '";
    script += organizer->count;
    script += "', Due_Date = '";
    script += organizer->due_date;
    script += "' WHERE ID = '";
    script += organizer->id;
    script += "';";
    
    return script;
}

string SQL::remove_organizer(Organizer* organizer){
    string script = "DELETE FROM organizers WHERE ID = '";
    script += organizer->id;
    script += "'; ";
    
    script += "DROP TABLE tasks_";
    script += organizer->id;
    script += "; ";
    
    return script;
}

string SQL::create_task(Task* task, Organizer* organizer){
    string script = "INSERT INTO tasks_";
    script += organizer->id;
    script += " VALUES('";
    script += task->id;
    script += "', '";
    script += task->name;
    script += "', '";
    script += task->date;
    script += "'); ";
    
    script += "CREATE TABLE subtasks_";
    script += task->id;
    script += "_";
    script += organizer->id;
    script += "(ID TEXT PRIMARY KEY NOT NULL UNIQUE, ";
    script += "Name TEXT NOT NULL, ";
    script += "Date TEXT NOT NULL);";
    
    return script;
}

string SQL::modify_task(Task* task, Organizer* organizer){
    string script = "UPDATE tasks_";
    script += organizer->id;
    script += " SET Name = '";
    script += task->name;
    script += "', Date = '";
    script += task->date;
    script += "' WHERE ID = '";
    script += task->id;
    script += "';";
    
    return script;
}

string SQL::remove_task(Task* task, Organizer* organizer){
    string script = "DELETE FROM tasks_";
    script += organizer->id;
    script += " WHERE ID = '";
    script += task->id;
    script += "'; ";
    
    script += "DROP TABLE subtasks_";
    script += task->id;
    script += "_";
    script += organizer->id;
    script += ";";
    
    return script;
}


string SQL::create_subtask(Subtask* subtask, Task* task, Organizer* organizer){
    string script = "INSERT INTO subtasks_";
    script += task->id;
    script += "_";
    script += organizer->id;
    script += " VALUES('";
    script += subtask->id;
    script += "', '";
    script += subtask->name;
    script += "', '";
    script += subtask->date;
    script += "');";
    
    return script;
}

string SQL::modify_subtask(Subtask* subtask, Task* task, Organizer* organizer){
    string script = "UPDATE subtasks_";
    script += task->id;
    script += "_";
    script += organizer->id;
    script += " SET Name = '";
    script += subtask->name;
    script += "', Date = '";
    script += subtask->date;
    script += "' WHERE ID = '";
    script += subtask->id;
    script += "';";
    
    return script;
}

string SQL::remove_subtask(Subtask* subtask, Task* task, Organizer* organizer){
    string script = "DELETE FROM subtasks_";
    script += task->id;
    script += "_";
    script += organizer->id;
    script += " WHERE ID = '";
    script += subtask->id;
    script += "';";
    
    return script;
}
