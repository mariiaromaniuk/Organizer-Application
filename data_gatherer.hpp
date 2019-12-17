//
//  data_gatherer.hpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#ifndef data_gatherer_hpp
#define data_gatherer_hpp

#include <stdio.h>
#include <iostream>
#include "database_handler.hpp"

#define GATHERER_NONE 0
#define GATHERER_ORGANIZER 1
#define GATHERER_TASK 2
#define GATHERER_SUBTASK 3

class DataGatherer{
public:
    DataGatherer();
    ~DataGatherer();
    static string get_selection(const int&, Organizer* = nullptr,
                                Task* = nullptr, Subtask* = nullptr);
    
    static bool confirm_delete();
    static Organizer* get_organizer_data();
    static Task* get_task_data();
    static Subtask* get_subtask_data();
};

#endif /* data_gatherer_hpp */
