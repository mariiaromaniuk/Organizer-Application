//
//  organizer.hpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#ifndef organizer_hpp
#define organizer_hpp

#include <stdio.h>
#include "task.hpp"

class Organizer{
public:
    string id;
    string title;
    string priority;
    string count;
    string due_date;
    
public:
    Organizer();
    Organizer(string, string, string, string, string);
    ~Organizer();
};

#endif /* organizer_hpp */
