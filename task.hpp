//
//  task.hpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#ifndef task_hpp
#define task_hpp

#include <stdio.h>
#include "subtask.hpp"

class Task{
public:
    string id;
    string name;
    string date;
    
public:
    Task();
    Task(string, string, string);
    ~Task();
};

#endif /* task_hpp */
