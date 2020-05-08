// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
//  crew.hpp
//  p1
//
//  Created by Connor Turco on 5/7/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#ifndef crew_hpp
#define crew_hpp

#include <stdio.h>
#include <deque>
#include <vector>

struct datum {
    bool discovered;
    char terrain;
    // 'f' if undiscovered
    char direction_from;
};
class crew {
public:
    crew();
    void set_captain_style(char style_in) {
        captain_style = style_in;
    }
    char get_captain_style() {
        return captain_style;
    }
    
    void set_first_mate_style(char style_in) {
        first_mate_style = style_in;
    }
    char get_fist_mate_style() {
        return first_mate_style;
    }
    //Recquires index is in range of array.
    void set_directions(int index, char char_in) {
        directions[index] = char_in;
    }
    void set_verbose(bool verbose_in) {
        verbose = verbose_in;
    }
    void set_display_stats(bool stats_in) {
        display_stats = stats_in;
    }
    void set_show_path(char path_in) {
        show_path = path_in;
    }
    void set_map(int row, int col, datum &data_in) {
        map_layout[row][col] = data_in;
    }
    void set_sail_location(std::pair<int, int> &start) {
        sail_location = start;
    }
    void map_resize(int capacity);
    void print_map() const;
    void discoverer(char type);
    
private:
    std::deque<std::pair<int, int>> captain;
    std::deque<std::pair<int, int>> first_mate;
    char captain_style;
    char first_mate_style;
    std::vector<std::vector<datum>> map_layout;
    char directions[4];
    bool print;
    std::pair<int, int> search_location;
    std::pair<int, int> sail_location;
    bool verbose;
    bool display_stats;
    char show_path;
    
    void direction_helper(int index, std::pair<int, int> &investigate);
    
    
    
    
    
};
#endif /* crew_hpp */
