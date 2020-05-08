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
    
    pair<int, int> default_style;
    default_style.first = -1;
    default_style.second = -1;
    search_location = default_style;
    sail_location = default_style;
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
    for(int i = 0; i < map_layout.size(); ++i) {
        for(int j = 0; j < map_layout.size(); ++j) {
            cout << map_layout[i][j].terrain;
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
            
            if(investigate != search_location) {
                //find undisvoered land location
                if(map_layout[investigate.first][investigate.second].terrain == 'o'
                   && map_layout[investigate.first][investigate.second].discovered == false) {
                    
                    map_layout[investigate.first][investigate.second].discovered = true;
                    map_layout[investigate.first][investigate.second].direction_from = opp_direction(i);
                    first_mate_push(investigate);
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
                    treasure_found = true;
                    return;
                }
                
            }
            
        }
    }
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
        if(row > map_layout.size() - 1) {
            return;
        }
        ++investigate.first;
        return;
    } // S
    
    if(directions[index] == 'e') {
        int col = investigate.second + 1;
        if(col > map_layout.size() - 1) {
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
        discoverer('l');
        if(treasure_found) {
            return true;
        }
        return false;
    }
    search_location.first = -1;
    search_location.second = -1;
    
    if(!captain.empty()) {
        search_location = captain_next();
    }
    discoverer('s');
    if(treasure_found) {
        return true;
    }
    return false;
    
    return false;
}
