// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
//  crew.cpp
//  p1
//
//  Created by Connor Turco on 5/7/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include "crew.hpp"
#include <vector>
#include <iostream>

using namespace std;

crew::crew() {
    captain_style = 's';
    first_mate_style = 'q';
    directions[0] = 'n';
    directions[1] = 'e';
    directions[2] = 's';
    directions[3] = 'w';
    verbose = false;
    display_stats = false;
    show_path = 'F';
    treasure_found = false;
    path_length = 0;
    
    pair<int, int> default_style;
    default_style.first = -1;
    default_style.second = -1;
    search_location = default_style;
    sail_location = default_style;
    start_location = default_style;
    treasure_location = default_style;
    
    //stats stuff
    num_sea_investigated = 1;
    num_land_investigated = 0;
    went_ashore = 0;
}
void crew::map_resize(int capacity) {
    datum default_datum;
    default_datum.discovered = false;
    default_datum.terrain = '.';
    default_datum.direction_from = 'f';
    
    map_layout.resize(capacity);
    for (int i = 0; i < capacity; ++i) {
        map_layout[i].resize(capacity);
    }
    for(int x = 0; x < capacity; ++x) {
        for(int j = 0; j < capacity; ++j) {
            map_layout[x][j] = default_datum;
        }
    }
}
void crew::print_map() const {
    for(int i = 0; i < (int)map_layout.size(); ++i) {
        for(int j = 0; j < (int)map_layout.size(); ++j) {
            cout << map_layout[i][j].terrain;
        }
        cout << "\n";
    }
}
void crew::print_map_discovered() const {
    for(int i = 0; i < (int)map_layout.size(); ++i) {
        for(int j = 0; j < (int)map_layout.size(); ++j) {
            cout << map_layout[i][j].discovered;
        }
        cout << "\n";
    }
}
void crew::discoverer(char type) {
    if(type == 'l') {
        for(int i = 0; i < 4; ++i) {
            pair<int, int> investigate = search_location;
            direction_helper(i, investigate);
            
            if(investigate != search_location) {
                //find undiscovered land location
                if(map_layout[investigate.first][investigate.second].terrain == 'o'
                   && map_layout[investigate.first][investigate.second].discovered == false) {
                    
                    map_layout[investigate.first][investigate.second].discovered = true;
                    first_mate_push(investigate);
                    map_layout[investigate.first][investigate.second].direction_from = opp_direction(i);
                }
                //Found treasure
                if(map_layout[investigate.first][investigate.second].terrain == '$') {
                    
                    map_layout[investigate.first][investigate.second].direction_from = opp_direction(i);
                    map_layout[investigate.first][investigate.second].discovered = true;
                    treasure_found = true;
                    return;
                }
            }
            
            
        }
    }
    if(type == 's') {
        for(int i = 0; i < 4; ++i) {
            pair<int, int> investigate = sail_location;
            direction_helper(i, investigate);
            
            if(investigate != sail_location) {
                //find undisvoered land location
                if(map_layout[investigate.first][investigate.second].terrain == 'o'
                   && map_layout[investigate.first][investigate.second].discovered == false) {
                    
                    map_layout[investigate.first][investigate.second].discovered = true;
                    map_layout[investigate.first][investigate.second].direction_from = opp_direction(i);
                    first_mate_push(investigate);
                    ++went_ashore;
                    break;
                }
                //if find undiscovered sea location
                if(map_layout[investigate.first][investigate.second].terrain == '.'
                   && map_layout[investigate.first][investigate.second].discovered == false) {
                    
                    map_layout[investigate.first][investigate.second].discovered = true;
                    map_layout[investigate.first][investigate.second].direction_from = opp_direction(i);
                    captain_push(investigate);
                    
                }
                //Treasure found
                if(map_layout[investigate.first][investigate.second].terrain == '$') {
                    
                    map_layout[investigate.first][investigate.second].direction_from = opp_direction(i);
                    map_layout[investigate.first][investigate.second].discovered = true;
                    //added hopefully this fixes
                    ++went_ashore;
                    treasure_found = true;
                    return;
                }
                
            }
            
        }
    }
//    cout << endl;
//    print_map_discovered();
    return;
}
//Changes pair to coordinates of one to that direction, if out of
//bounds, doesn't change pair
void crew::direction_helper(int index, pair<int, int> &investigate) {
    if(directions[index] == 'n') {
        int row = investigate.first - 1;
        if(row < 0) {
            return;
        }
        --investigate.first;
        return;
    } // N
    
    if(directions[index] == 's') {
        int row = investigate.first + 1;
        if(row > (int)map_layout.size() - 1) {
            return;
        }
        ++investigate.first;
        return;
    } // S
    
    if(directions[index] == 'e') {
        int col = investigate.second + 1;
        if(col > (int)map_layout.size() - 1) {
            return;
        }
        ++investigate.second;
        return;
    } // E
    
    if(directions[index] == 'w') {
        int col = investigate.second - 1;
        if(col < 0) {
            return;
        }
        --investigate.second;
        return;
    } // E
}
void crew::captain_pop() {
    captain.pop_front();
}
void crew::first_mate_pop() {
    first_mate.pop_front();
}
void crew::first_mate_push(std::pair<int, int> &coordinate) {
    if(first_mate_style == 'q') {
        first_mate.push_back(coordinate);
    }
    if(first_mate_style == 's') {
        first_mate.push_front(coordinate);
    }
}
void crew::captain_push(std::pair<int, int> &coordinate) {
    if(captain_style == 'q') {
        captain.push_back(coordinate);
    }
    if(captain_style == 's') {
        captain.push_front(coordinate);
    }
}
std::pair<int, int> &crew::first_mate_next() {
    return first_mate.front();
}
std::pair<int, int> &crew::captain_next() {
    return captain.front();
}
char crew::opp_direction(int index) {
    if(directions[index] == 'n') {
        return 's';
    }
    if(directions[index] == 's') {
        return 'n';
    }
    if(directions[index] == 'e') {
        return 'w';
    }
    else {
        return 'e';
    }
}
bool crew::mover(){
    if(!first_mate.empty()) {
        search_location = first_mate_next();
        first_mate_pop();
        ++num_land_investigated;
        discoverer('l');
        if(treasure_found) {
            ++num_land_investigated;
            print_searching_island();
            return true;
        }
        return false;
    }
    //coming back from sea search
    if(search_location.first == -1 && !captain.empty()) {
        sail_location = captain_next();
        captain_pop();
        ++num_sea_investigated;
    }
    
    discoverer('s');
    //coming back from land search
    if(search_location.first != -1) {
        search_location.first = -1;
        search_location.second = -1;
        print_searching_island();
    }


    if(!first_mate.empty()) {
        print_went_ashore();
    }
    //Treasure found by sea
    if(treasure_found) {
        print_went_ashore();
        print_searching_island();
        ++num_land_investigated;
        return true;
    }
    //found no treasure
    if(first_mate.empty() && captain.empty()) {
        return true;
    }
    return false;
    
    return false;
}   
void crew::print_start() {
    if(verbose) {
        cout << "Treasure hunt started at: " << start_location.first << ","
        << start_location.second << "\n";
    }
}
void crew::print_went_ashore() {
    if(verbose) {
        if(treasure_found) {
            cout << "Went ashore at: " << treasure_location.first << ","
            << treasure_location.second << "\n";
            return;
        }
        cout << "Went ashore at: " << first_mate_next().first << ","
        << first_mate_next().second << "\n";
        
    }
}
void crew::print_searching_island() {
    if(verbose) {
        cout << "Searching island... party ";
        if(treasure_found) {
            cout << "found treasure at " << treasure_location.first
            << "," << treasure_location.second << ".\n";
            return;
        }
        cout << "returned with no treasure.\n";
    }

}
void crew::direction_helper_path(char direction_from, std::pair<int, int> &investigate) {
    if(direction_from == 'n') {
        int row = investigate.first - 1;
        if(row < 0) {
            return;
        }
        --investigate.first;
        return;
    } // N
    
    if(direction_from == 's') {
        int row = investigate.first + 1;
        if(row > (int)map_layout.size() - 1) {
            return;
        }
        ++investigate.first;
        return;
    } // S
    
    if(direction_from == 'e') {
        int col = investigate.second + 1;
        if(col > (int)map_layout.size() - 1) {
            return;
        }
        ++investigate.second;
        return;
    } // E
    
    if(direction_from == 'w') {
        int col = investigate.second - 1;
        if(col < 0) {
            return;
        }
        --investigate.second;
        return;
    } // E
}
void crew::find_path() {
    if(!treasure_found) {
        return;
    }
    pair<int, int> back = treasure_location;
    pair<int, int> front = treasure_location;
    char back_direction = map_at(back).direction_from;
    
    direction_helper_path(map_at(back).direction_from, front);
    //push treasure onto land vector
    land_search.push_back(back);
    
    while(map_at(front).terrain != '@') {
        
        //sets front direction
        char front_direction = map_at(front).direction_from;
        
        if(map_at(front).terrain == 'o') {
            land_search.push_back(front);
        }
        else {
            sea_search.push_back(front);
        }
        
        //sets front to proper direction terrain
        if(direction_change(front_direction, back_direction)) {
            map_at(front).terrain = '+';
        }
        else {
            map_at(front).terrain = proper_char(front_direction);
        }
        back = front;
        back_direction = front_direction;
        direction_helper_path(map_at(back).direction_from, front);
        ++path_length;
    }
    map_at(treasure_location).terrain = 'X';
    ++path_length;
    sea_search.push_back(front);
}
datum &crew::map_at(std::pair<int, int> &pair) {
    return map_layout[pair.first][pair.second];
}
bool crew::direction_change(char d1, char d2) {
    bool up = false;
    bool side = false;
    
    if(d1 == 'n' || d1 == 's' || d2 == 'n' || d2 == 's') {
        up = true;
    }
    if(d1 == 'e' || d1 == 'w' || d2 == 'e' || d2 == 'w') {
        side = true;
    }
    if(up && side) {
        return true;
    }
    return false;
}
char crew::proper_char(char direction) {
    if(direction == 'w' || direction == 'e') {
        return '-';
    }
    return '|';
}
void crew::print_stats() {
    if(!display_stats) {
        return;
    }
    cout << "--- STATS ---\n"
    << "Starting location: " << start_location.first << "," << start_location.second
    << "\n"
    << "Water locations investigated: " << num_sea_investigated << "\n"
    << "Land locations investigated: " << num_land_investigated << "\n"
    << "Went ashore: " << went_ashore << "\n"
    << "Path length: " << path_length << "\n"
    << "Treasure location: " << treasure_location.first << "," << treasure_location.second << "\n"
    << "--- STATS ---\n";
}
void crew::print_show_path() {
    if(show_path == 'F') {
        return;
    }
    if(!treasure_found) {
        return;
    }
    if(show_path == 'M') {
        print_map();
        return;
    }
    cout << "Sail:\n";
    for(auto it = sea_search.end() - 1; it >= sea_search.begin(); --it) {
        cout << it->first << "," << it->second << "\n";
    }
    cout << "Search:\n";
    for(auto it = land_search.end() - 1; it >= land_search.begin(); --it) {
        cout << it->first << "," << it->second << "\n";
    }
}

void crew::print_final_line() {
    if(treasure_found) {
        cout << "Treasure found at " << treasure_location.first << ","
        << treasure_location.second << " with path length " << path_length << ".\n";
        return;
    }
    cout << "No treasure found after investigating "
    << num_sea_investigated + num_land_investigated << " locations.\n";
    
}
