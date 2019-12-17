//
//  sql.hpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#ifndef sql_hpp
#define sql_hpp

#include "organizer.hpp"
#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;


class SQL{
public:
    static string create_organizer_main_table();
    
    static string create_organizer(Organizer*);
    static string modify_organizer(Organizer*);
    static string remove_organizer(Organizer*);
    
    static string create_task(Task*, Organizer*);
    static string modify_task(Task*, Organizer*);
    static string remove_task(Task*, Organizer*);
    
    static string create_subtask(Subtask*, Task*, Organizer*);
    static string modify_subtask(Subtask*, Task*, Organizer*);
    static string remove_subtask(Subtask*, Task*, Organizer*);
};

#endif /* sql_hpp */
