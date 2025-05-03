#ifndef SIMULATION_H
#define SIMULATION_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include"world_type.h"

bool if_file_open_successful(std::string str);
//return true if the file can be opened successfully

bool if_exceed_max(std::string str,int max);
//return true if the number of ... in the files don't exceed the max

bool if_instruction_legal(const std::string instruction);
//return true if the instruction is legal

opcode_t str_to_opcode(const std::string instruction);
//convert string to the corresbonding opcode

void initialize_species(world_t& world, std::ifstream& ifile);
//initialize the species of the world
//MODIFIES: the world

void initial_grid(world_t& world, std::ifstream& ifile);
//initialize the grid of the world
//MODIFIES: the world

void initial_creature(world_t& world, std::ifstream& ifile);
//initialize the creature of the world
//MODIFIES: the world

species_t* str_to_species(world_t& world, std::string str);
//convert the string to the corresponding species

direction_t str_to_direction(std::string str);
//convert string to the corresbonding direction

void overlap_test(world_t& world);
//test whether their is oberlapping in the world


void print_world(const world_t& world);
//print the world

void left(world_t& world,int creature_num);

void right(world_t& world,int creature_num);

void hop(world_t& world,int creature_num);

point_t front(world_t& world,int creature_num);
//return the point the creature faces
void infect(world_t& world,int creature_num);

void go(world_t& world,int creature_num);

void ifempty(world_t& world,int creature_num);

bool if_not_boundary(world_t& world,int creature_num);
//return true if the creature isn't facing the boundary
void ifenemy(world_t& world,int creature_num);

void ifsame(world_t& world,int creature_num);

void ifwall(world_t& world,int creature_num);

bool if_instrcution_basic(world_t& world,int creature_num);

void simulation_concise(world_t& world);
//simulation the game!

void simulation_v(world_t& world);

std::string take_action(world_t& world,int creature_num);

void instruction_ifgo(world_t& world,int creature_num);

void instruction_normal(world_t& world,int creature_num);
#endif
