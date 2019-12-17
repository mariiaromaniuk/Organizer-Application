//
//  subtask.hpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#ifndef subtask_hpp
#define subtask_hpp

#include <stdio.h>
#include <string>
using namespace std;


class Subtask{
public:
    string id;
    string name;
    string date;
    
public:
    Subtask();
    Subtask(string, string, string);
    ~Subtask();
};

#endif /* subtask_hpp */
