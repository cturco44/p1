// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
//  hunt.cpp
//  p1
//
//  Created by Connor Turco on 5/7/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include "crew.hpp"
#include <cassert>


using namespace std;

void getArgs(int argc, char * argv[], crew &crew_in) {
    
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        {"help",       no_argument,       nullptr, 'h'},
        {"captain",    required_argument, nullptr, 'c'},
        {"first-mate", required_argument, nullptr, 'f'},
        {"hunt-order", required_argument, nullptr, 'o'},
        {"vecbose",    no_argument,       nullptr, 'v'},
        {"stats",      no_argument,       nullptr, 's'},
        {"show-path",  required_argument, nullptr, 'p'},
        { nullptr, 0,                 nullptr, '\0' }
    };
    opterr = true; // Give us help with errors
    int choice;
    int option_index = 0;

   
    while ((choice = getopt_long(argc, argv, "hc:f:o:vsp:", long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h': {
                //TODO: Set useful message to something useful
                cout << "useful message \n";
                break;
            } // case h
            case 'c': {
                string str = string(optarg);
                if(str == "queue") {
                    crew_in.set_captain_style('q');
                }
                if(str == "stack") {
                    crew_in.set_captain_style('s');
                }
                else {
                    exit(1);
                }
                break;
            } // case c
                
            case 'f': {
                string str = string(optarg);
                if(str == "queue") {
                    crew_in.set_first_mate_style('q');
                }
                if(str == "stack") {
                    crew_in.set_first_mate_style('s');
                }
                else {
                    exit(1);
                }
                break;
            } //case f
                
            case 'o': {
                if(strlen(optarg) != 4) {
                    exit(1);
                }
                for(int i = 0; i < 4; ++i) {
                    crew_in.set_directions(i, optarg[i]);
                }
                break;
            } //case o
                
            case 'v': {
                crew_in.set_verbose(true);
                break;
            } // case v
            case 's':
                crew_in.set_display_stats(true);
                break;
            case 'p': {
                string str = string(optarg);
                if(str.length() != 1) {
                    exit(1);
                }
                if(str[0] != 'M' && str[0] != 'L') {
                    exit(1);
                }
                crew_in.set_show_path(str[0]);
                break;
            } // case p
                
                
        default:
            cerr << "Error: invalid option\n";
            exit(1);
        } // switch
    } // while
    
    return;
} // getMode()

void read_map(crew &crew_in) {
    char first;
    cin >> first;
    while(first == '#') {
        string s;
        getline(cin, s);
        cin >> first;
    }
    int capacity;
    cin >> capacity;
    crew_in.map_resize(capacity);
    
    string s;
    //gets endline
    getline(cin, s);
    if(first == 'L') {
        while(getline(cin, s)) {
            if(static_cast<int>(s.length()) == 5) {
                
                int row = s[0] - '0';
                int col = s[2] - '0';
                char terrain = s[4];
                
                if(terrain == '@') {
                    pair<int, int> start (row, col);
                    crew_in.set_sail_location(start);
                }
                if(terrain == '$') {
                    pair<int, int> start (row, col);
                    crew_in.set_treasure_location(start);
                }
                if(terrain != '.') {
                    datum data_in;
                    data_in.discovered = false;
                    data_in.terrain = terrain;
                    data_in.direction_from = 'f';
                    
                    crew_in.set_map(row, col, data_in);
                }
            }
        }
        return;
    }
    if(first == 'M') {
        int row = 0;
        datum data_in;
        data_in.discovered = false;
        data_in.direction_from = 'f';
        
        while(getline(cin, s)) {
            //if its a valid line
            if(s.length() == capacity) {
                for(int col = 0; col < capacity; ++col) {
                    if(s[col] != '.') {
                        if(s[col] == '@') {
                            pair<int, int> start (row, col);
                            crew_in.set_sail_location(start);
                        }
                        if(s[col] == '$') {
                            pair<int, int> start (row, col);
                            crew_in.set_treasure_location(start);
                        }
                        data_in.terrain = s[col];
                        crew_in.set_map(row, col, data_in);
                    } // != .
                } // for col
            }//if length
            ++row;
        } // while getline
        return;
    }
    
    return;
}
int main(int argc, char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    crew maincrew;
    getArgs(argc, argv, maincrew);
    read_map(maincrew);
    
    maincrew.print_start();
    while (!maincrew.mover()) {
    }
    
    maincrew.find_path();
    maincrew.print_stats();
    maincrew.print_show_path();
    maincrew.print_final_line();
   
    return 0;
}
