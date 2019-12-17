//
//  app.cpp
//  organizer
//
//  Created by Mariia Romaniuk
//

#include "gui.hpp"

// Current Objects
vector<Organizer*> organizers;
Organizer* current_organizer = nullptr;

vector<Task*> tasks;
Task* current_task = nullptr;

vector<Subtask*> subtasks;
Subtask* current_subtask = nullptr;

// Current UI
bool organizer_ui = true;
bool task_ui = false;
bool subtask_ui = false;
bool subtask_detail_ui = false;


int main(int argc, char const *argv[]){
    // Variables
    string choice;
    DatabaseHandler* db_handler = new DatabaseHandler("organizer.sqlite");
    
    // Welcome
    GUI::welcome();
    
    // Choose between UIs
    while (true){
        if (organizer_ui){
            // 1. Organizer options
            GUI::organizer_options();
            
            // Ask for selection
            choice = DataGatherer::get_selection(GATHERER_NONE);
            
            // Choose
            if (choice == "1"){
                // 1. Create organizer
                
                // Gather data
                current_organizer = DataGatherer::get_organizer_data();
                
                // Save to database
                bool success = db_handler->perform_action(DATABASE_CREATE,
                                                          current_organizer);
                
                if (!success){
                    GUI::error(GUI_CREATE, current_organizer);
                    continue;
                }
                
            } else if (choice == "2") {
                // 2. Select organizer
                organizers = db_handler->get_all_organizers();
                if (organizers.size() == 0) continue;
                
                GUI::display_organizers(organizers);
                
                // Ask for choice
                choice = DataGatherer::get_selection(GATHERER_NONE);
                
                // Set current organizer object
                int index = stoi(choice) - 1;
                current_organizer = organizers[index];
                
                // Switch to task UI
                organizer_ui = false;
                task_ui = true;
                
            } else {
                break;
            }
            
            
        } else if (task_ui){
            // 2. Tasks options
            GUI::task_options();
            
            // Ask for selection
            choice = DataGatherer::get_selection(GATHERER_ORGANIZER,
                                                 current_organizer);
            
            // Choose
            if (choice == "1"){
                // 1. Modify current organizer
                
                // Gather data
                current_organizer = DataGatherer::get_organizer_data();
                
                // Save to database
                bool success = db_handler->perform_action(DATABASE_MODIFY,
                                                          current_organizer);
                
                if (!success){
                    GUI::error(GUI_MODIFY, current_organizer);
                    continue;
                }
                
            } else if (choice == "2"){
                // 2. Delete current organizer
                
                // Confirm
                bool yes = DataGatherer::confirm_delete();
                
                // Delete from database and from current variables
                if (yes){
                    bool success = db_handler->perform_action(
                                                              DATABASE_REMOVE, current_organizer);
                    
                    if (!success){
                        GUI::error(GUI_DELETE, current_organizer);
                        continue;
                    }
                    
                    for (int i = 0; i < organizers.size(); ++i){
                        if (organizers[i]->id == current_organizer->id) {
                            organizers.erase(organizers.begin() + i);
                            break;
                        }
                    }
                    
                    current_organizer = nullptr;
                    
                    // switch back to organizers UI
                    organizer_ui = true;
                    task_ui = false;
                }
                
                continue;
                
            } else if (choice == "3"){
                // 3. Create task
                
                // Gather data
                current_task = DataGatherer::get_task_data();
                
                // Save to database
                bool success = db_handler->perform_action(
                                                          DATABASE_CREATE, current_organizer, current_task);
                
                if (!success){
                    GUI::error(GUI_CREATE, nullptr, current_task);
                    continue;
                }
                
            } else if (choice == "4"){
                // 4. Select person
                tasks = db_handler->get_all_tasks(current_organizer);
                if (tasks.size() == 0) continue;
                
                GUI::display_tasks(tasks);
                
                // Ask for choice
                choice = DataGatherer::get_selection(GATHERER_ORGANIZER,
                                                     current_organizer);
                
                // Switch to subtasks UI
                int index = stoi(choice) - 1;
                current_task = tasks[index];
                task_ui = false;
                subtask_ui = true;
                
                continue;
                
            } else if (choice == "5"){
                organizer_ui = true;
                task_ui = false;
                
            } else {
                break;
            }
            
        } else if (subtask_ui){
            // 3. Subtask options
            GUI::subtask_options();
            
            // Ask for selection
            choice = DataGatherer::get_selection(GATHERER_TASK,
                                                 current_organizer, current_task);
            
            // Choose
            if (choice == "1"){
                // 1. Modify task
                
                // Gather data
                current_task = DataGatherer::get_task_data();
                
                // Save to database
                bool success = db_handler->perform_action(DATABASE_MODIFY,
                                                          current_organizer, current_task);
                
                if (!success){
                    GUI::error(GUI_MODIFY, nullptr, current_task);
                    continue;
                }
                
            } else if (choice == "2") {
                // 2. Delete task
                
                // Confirm
                bool yes = DataGatherer::confirm_delete();
                
                // Delete from database
                if (yes){
                    bool success = db_handler->perform_action(DATABASE_REMOVE,
                                                              current_organizer, current_task);
                    
                    if (!success){
                        GUI::error(GUI_DELETE, nullptr, current_task);
                        continue;
                    }
                    
                    for (int i = 0; i < tasks.size(); ++i){
                        if (tasks[i]->id == current_task->id){
                            tasks.erase(tasks.begin() + i);
                            break;
                        }
                    }
                    
                    current_task = nullptr;
                    
                    // switch back to tasks UI
                    task_ui = true;
                    subtask_ui = false;
                    
                    continue;
                }
                
            } else if (choice == "3"){
                // 3. Create subtask
                
                // Gather data
                current_subtask = DataGatherer::get_subtask_data();
                
                // Save to database
                bool success = db_handler->perform_action(DATABASE_CREATE,
                                                          current_organizer, current_task, current_subtask);
                
                if (!success){
                    GUI::error(GUI_CREATE, nullptr, nullptr, current_subtask);
                    continue;
                }
                
            } else if (choice == "4") {
                // 4. Select subtask
                subtasks = db_handler->get_all_subtasks(current_task,
                                                        current_organizer);
                if (subtasks.size() == 0) continue;
                
                GUI::display_subtasks(subtasks);
                
                // Ask for choice
                choice = DataGatherer::get_selection(GATHERER_TASK,
                                                     current_organizer, current_task);
                
                // create current subtask object
                int index = stoi(choice) - 1;
                current_subtask = subtasks[index];
                
                // Switch for subtask choices UI
                subtask_ui = false;
                subtask_detail_ui = true;
                
            } else if (choice == "5") {
                task_ui = true;
                subtask_ui = false;
                
            } else {
                break;
            }
            
        } else if (subtask_detail_ui){
            // 4. Subtasks detail options
            GUI::subtask_details();
            
            // Ask for selection
            choice = DataGatherer::get_selection(GATHERER_SUBTASK,
                                                 current_organizer, current_task, current_subtask);
            
            // Choose
            if (choice == "1"){
                // 1. Modify subtask
                
                // Gather data
                current_subtask = DataGatherer::get_subtask_data();
                
                // Save to database
                bool success = db_handler->perform_action(DATABASE_MODIFY,
                                                          current_organizer, current_task, current_subtask);
                
                if (!success){
                    GUI::error(GUI_MODIFY, nullptr, nullptr, current_subtask);
                    continue;
                }
                
            } else if (choice == "2"){
                // 2. Delete subtask
                
                // Confirm
                bool yes = DataGatherer::confirm_delete();
                
                // Delete from database
                if (yes){
                    bool success = db_handler->perform_action(
                                                              DATABASE_REMOVE, current_organizer,
                                                              current_task, current_subtask);
                    
                    if (!success){
                        GUI::error(GUI_DELETE, nullptr, nullptr, current_subtask);
                        continue;
                    }
                    
                    for (int i = 0; i < subtasks.size(); ++i){
                        if (subtasks[i]->id == current_subtask->id){
                            subtasks.erase(subtasks.begin() + i);
                            break;
                        }
                    }
                    
                    current_subtask = nullptr;
                    
                    // switch back to tasks UI
                    subtask_ui = true;
                    subtask_detail_ui = false;
                    
                    continue;
                }
                
            } else if (choice == "3"){
                subtask_ui = true;
                subtask_detail_ui = false;
                
            } else {
                break;
            }
        }
    }
    
    delete db_handler;
    
    return 0;
}
