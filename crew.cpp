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
