//
//  gui.hpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#ifndef gui_hpp
#define gui_hpp

#include <stdio.h>
#include "data_gatherer.hpp"

#define GUI_CREATE 0
#define GUI_MODIFY 1
#define GUI_DELETE 2

#define TW 20
#define NW 10

class GUI{
public:
    GUI();
    ~GUI();
    
    static void welcome();
    
    static void organizer_options();
    static void display_organizers(vector<Organizer*>);
    
    static void task_options();
    static void display_tasks(vector<Task*>);
    
    static void subtask_options();
    static void display_subtasks(vector<Subtask*>);
    static void subtask_details();
    
    static void error(const int&, Organizer* = nullptr, Task* = nullptr,
                      Subtask* = nullptr);
    
private:
    static constexpr int FIELD_WIDTH = 15;
};

#endif /* gui_hpp */
