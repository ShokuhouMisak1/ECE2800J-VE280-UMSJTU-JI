#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include"world_type.h"
#include"simulation.h"

bool if_file_open_successful(std::string str){
    std::ifstream ifile(str);
    if(!ifile) return false;
    ifile.close();
    return true;
}

bool if_exceed_max(std::string str,int max){
    std::ifstream ifile;
    ifile.open(str);
    std::string temp;
    int num = 0;
    while(ifile>>temp) num++;
    ifile.close();
    if(num>max) return false;
    return true;
}

bool if_instruction_legal(const std::string instruction){
    for(unsigned int i=0; i<=8;i++){
        if(instruction == opName[i]) return true;
    }
    return false;
}

opcode_t str_to_opcode(const std::string instruction){
    if(instruction == "hop") return HOP;
    if(instruction == "left") return LEFT;
    if(instruction == "right") return RIGHT;
    if(instruction == "infect") return INFECT;
    if(instruction == "ifempty") return IFEMPTY;
    if(instruction == "ifenemy") return IFENEMY;
    if(instruction == "ifsame") return IFSAME;
    if(instruction == "ifwall") return IFWALL;
    return GO;
}

void initialize_species(world_t& world, std::ifstream& ifile){
    std::string species_dir;
    std::string species_name;
    world.numSpecies = 0;
    ifile>>species_dir;
    while(ifile>>species_name){
        std::string fullPath = species_dir + "/" + species_name;
        if(!if_file_open_successful(fullPath)){
            std::cout<<"Error: Cannot open file "<<fullPath<<"! ";
            exit(0);
        }
        //Check whether the object species file can open successfully
        world.species[world.numSpecies].name = species_name;
        std::ifstream species(fullPath);
        std::string species_per_line;
        world.species[world.numSpecies].programSize =0;
        while(getline(species,species_per_line)){
            if(species_per_line.empty()) break;
            // if there is an empty line, omit the comments below and quit
            world.species[world.numSpecies].programSize++;
            if(world.species[world.numSpecies].programSize>MAXPROGRAM){
                std::cout<<"Error: Too many instructions for species " << world.species[world.numSpecies].name<<"! ";
                std::cout<<"Maximal number of instructions is "<< MAXPROGRAM << ". ";
                exit(0);
            }
            //  Check whether the number of instructions for a species exceeds the maximal size of a species program MAXPROGRAM.
            std::string temp;
            std::istringstream is(species_per_line);
            is>>temp;
            if(!if_instruction_legal(temp)){
                std::cout<<"Error: Instruction "<<temp<<" is not recognized! ";
                exit(0);
            }
            //Check whether the species program file contains illegal instructions.
            world.species[world.numSpecies].program[world.species[world.numSpecies].programSize-1].op=str_to_opcode(temp);
            if(str_to_opcode(temp)>3){  //judge whether the op has address
                is>>temp;
                world.species[world.numSpecies].program[world.species[world.numSpecies].programSize-1].address = std::stoi(temp);
            }
        }
        world.numSpecies++;
    }
}

void initial_grid(world_t& world, std::ifstream& ifile){
    std::string world_per_line;
    getline(ifile,world_per_line);
    world.grid.height = stoi(world_per_line);
    getline(ifile,world_per_line);
    world.grid.width = stoi(world_per_line);
    if(world.grid.height>MAXHEIGHT || world.grid.height<1){
        std::cout<< "Error: The grid height is illegal! "<<std::endl;
        exit(0);
    }
    if(world.grid.width>MAXWIDTH || world.grid.width<1){
        std::cout<< "Error: The grid width is illegal! "<<std::endl;
        exit(0);
    }
}

void initial_creature(world_t& world, std::ifstream& ifile){
    std::string creature_per_line;
    world.numCreatures = 0;
    while(getline(ifile,creature_per_line)){
        if(creature_per_line == "") break;
        world.numCreatures++;
        if(world.numCreatures>MAXCREATURES){
            std::cout<<"Error: Too many creatures! "<<std::endl;
            std::cout<<"Maximal number of creatures is "<< MAXCREATURES <<". "<<std::endl;
            exit(0);
        }
        std::istringstream is(creature_per_line);
        std::string temp;
        is>>temp;
        world.creatures[world.numCreatures-1].species = str_to_species(world,temp);
        is>>temp;
        world.creatures[world.numCreatures-1].direction = str_to_direction(temp);
        is>>temp;
        world.creatures[world.numCreatures-1].location.r = stoi(temp);
        is>>temp;
        world.creatures[world.numCreatures-1].location.c = stoi(temp);
        if(world.creatures[world.numCreatures-1].location.r<0 ||(unsigned int)world.creatures[world.numCreatures-1].location.r>=world.grid.height || world.creatures[world.numCreatures-1].location.c<0 ||(unsigned int)world.creatures[world.numCreatures-1].location.c>=world.grid.width){
            std::cout<<"Error: Creature ("<< world.creatures[world.numCreatures-1].species->name <<" "<<directName[world.creatures[world.numCreatures-1].direction] <<" "<<world.creatures[world.numCreatures-1].location.r<<" "<<world.creatures[world.numCreatures-1].location.c<<") is out of bound! "<<std::endl;
            std::cout<<"The grid size is "<<world.grid.height<<"-by-"<<world.grid.width<<".";
            exit(0);
        }
        world.creatures[world.numCreatures-1].programID = 1;
    }
    overlap_test(world);
}

species_t* str_to_species(world_t& world, std::string str){
    for(unsigned int i=0;i<world.numSpecies;i++){
        if(str == world.species[i].name){
            return &world.species[i];
        }
    }
    std::cout<<"Error: Species "<<str<<" not found! "<<std::endl;
    exit(0);
    return nullptr;
}

direction_t str_to_direction(std::string str){
    if(str == "east") return EAST;
    if(str == "west") return WEST;
    if(str == "south") return SOUTH;
    if(str == "north") return NORTH;
    std::cout<<"Error: Direction "<<str<<" is not recognized! "<<std::endl;
    exit(0);
    return EAST;
}

void overlap_test(world_t& world){
    for(unsigned int i=0;i<world.grid.height;i++){
        for(unsigned int j=0;j<world.grid.width;j++){
            world.grid.squares[i][j] = NULL;
        }
    }
    for(unsigned int i=0;i<world.numCreatures;i++){
        if(world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c] != NULL){
            std::cout<<"Error: Creature ("<<world.creatures[i].species->name<<" "<<directName[world.creatures[i].direction]<<" "<<world.creatures[i].location.r<<" "<<world.creatures[i].location.c<<") overlaps with creature ("<< world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c]->species->name<<" "<<directName[world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c]->direction]<<" "<<world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c]->location.r<<" "<<world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c]->location.c<<")! ";
            exit(0);
        }
        else{
            world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c] = &world.creatures[i];
        }
    }
}

void print_world(const world_t& world){
    for(unsigned int i=0;i<world.grid.height;i++){
        for(unsigned int j=0;j<world.grid.width;j++){
            if(world.grid.squares[i][j] == NULL)  std::cout<<"____ ";
            else{
                std::cout<<world.grid.squares[i][j]->species->name[0]<<world.grid.squares[i][j]->species->name[1]<<"_"<<directShortName[world.grid.squares[i][j]->direction]<<" ";
            }
        }
        std::cout<<std::endl;
    }
}

void left(world_t& world,int creature_num){
    if(world.creatures[creature_num].direction != EAST) world.creatures[creature_num].direction = direction_t(world.creatures[creature_num].direction - 1);
    else world.creatures[creature_num].direction = NORTH;
    world.creatures[creature_num].programID++;
}

void right(world_t& world,int creature_num){
    if(world.creatures[creature_num].direction != NORTH) world.creatures[creature_num].direction = direction_t(world.creatures[creature_num].direction + 1);
    else world.creatures[creature_num].direction = EAST;
    world.creatures[creature_num].programID++;
}

void hop(world_t& world,int creature_num){
    if(world.grid.squares[front(world,creature_num).r][front(world,creature_num).c] == NULL){
        world.grid.squares[world.creatures[creature_num].location.r][world.creatures[creature_num].location.c] = NULL;
        world.creatures[creature_num].location = front(world,creature_num);
        world.grid.squares[world.creatures[creature_num].location.r][world.creatures[creature_num].location.c] = &world.creatures[creature_num];
    }
    world.creatures[creature_num].programID++;
}

point_t front(world_t& world,int creature_num){
    if(world.creatures[creature_num].direction == WEST){
        if(world.creatures[creature_num].location.c == 0) return{world.creatures[creature_num].location.r,world.creatures[creature_num].location.c};
        return {world.creatures[creature_num].location.r,world.creatures[creature_num].location.c-1};
    }
    if(world.creatures[creature_num].direction == EAST){
        if((unsigned int)world.creatures[creature_num].location.c == (world.grid.width-1)) return{world.creatures[creature_num].location.r,world.creatures[creature_num].location.c};
        return {world.creatures[creature_num].location.r,world.creatures[creature_num].location.c+1};
    }
    if(world.creatures[creature_num].direction == NORTH){
        if(world.creatures[creature_num].location.r == 0) return{world.creatures[creature_num].location.r,world.creatures[creature_num].location.c};
        return {world.creatures[creature_num].location.r-1,world.creatures[creature_num].location.c};
    }
    if(world.creatures[creature_num].direction == SOUTH){
        if((unsigned int)world.creatures[creature_num].location.r == (world.grid.height-1)) return{world.creatures[creature_num].location.r,world.creatures[creature_num].location.c};
        return {world.creatures[creature_num].location.r+1,world.creatures[creature_num].location.c};
    }
    return{0,0};
}

void infect(world_t& world,int creature_num){
    if(world.grid.squares[front(world,creature_num).r][front(world,creature_num).c] != NULL){
        if(world.grid.squares[front(world,creature_num).r][front(world,creature_num).c]->species != world.creatures[creature_num].species){
            world.grid.squares[front(world,creature_num).r][front(world,creature_num).c]->species = world.creatures[creature_num].species;
            world.grid.squares[front(world,creature_num).r][front(world,creature_num).c]->programID = 1;
        }
    }
    world.creatures[creature_num].programID++;
}

void go(world_t& world,int creature_num){
    world.creatures[creature_num].programID = world.creatures[creature_num].species->program[world.creatures[creature_num].programID-1].address;
}

void ifempty(world_t& world,int creature_num){
    if(if_not_boundary(world,creature_num)){
        if(world.grid.squares[front(world,creature_num).r][front(world,creature_num).c] == NULL){
            go(world,creature_num);
            return;
        }
    }
    world.creatures[creature_num].programID++;
}

bool if_not_boundary(world_t& world,int creature_num){
    if(world.creatures[creature_num].direction == WEST){
        if(world.creatures[creature_num].location.c == 0) return false;
    }
    if(world.creatures[creature_num].direction == EAST){
        if((unsigned int)world.creatures[creature_num].location.c == (world.grid.width-1)) return false;
    }
    if(world.creatures[creature_num].direction == NORTH){
        if(world.creatures[creature_num].location.r == 0) return false;
    }
    if(world.creatures[creature_num].direction == SOUTH){
        if((unsigned int)world.creatures[creature_num].location.r == (world.grid.height-1)) return false;
    }
    return true;
}

void ifenemy(world_t& world,int creature_num){
    if(if_not_boundary(world,creature_num)){
        if(world.grid.squares[front(world,creature_num).r][front(world,creature_num).c] != NULL){
            if(world.grid.squares[front(world,creature_num).r][front(world,creature_num).c]->species != world.creatures[creature_num].species){
                go(world,creature_num);
                return;
            }
        }
    }
    world.creatures[creature_num].programID++;
}

void ifsame(world_t& world,int creature_num){
    if(if_not_boundary(world,creature_num)){
        if(world.grid.squares[front(world,creature_num).r][front(world,creature_num).c] != NULL){
            if(world.grid.squares[front(world,creature_num).r][front(world,creature_num).c]->species == world.creatures[creature_num].species){
                go(world,creature_num);
                return;
            }
        }
    }
    world.creatures[creature_num].programID++;
}

void ifwall(world_t& world,int creature_num){
    if(!if_not_boundary(world,creature_num)){
        go(world,creature_num);
    }
    else world.creatures[creature_num].programID++;
}

void simulation_concise(world_t& world){
    for(unsigned int j=0;j<world.numCreatures;j++){
        while(!if_instrcution_basic(world,j)){
        if(world.creatures[j].species->program[world.creatures[j].programID-1].op == GO) go(world,j);
        else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == IFEMPTY) ifempty(world,j);
        else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == IFENEMY) ifenemy(world,j);
        else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == IFSAME) ifsame(world,j);
        else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == IFWALL) ifwall(world,j);
        }
        if(world.creatures[j].species->program[world.creatures[j].programID-1].op == LEFT){
            std::cout<<take_action(world,j)<<"left"<<std::endl;
            left(world,j);
        }
        else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == RIGHT){
            std::cout<<take_action(world,j)<<"right"<<std::endl;
            right(world,j);
        }
        else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == HOP){
            std::cout<<take_action(world,j)<<"hop"<<std::endl;
            hop(world,j);
        }
        else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == INFECT){
            std::cout<<take_action(world,j)<<"infect"<<std::endl;
            infect(world,j);
        }
    }
}

bool if_instrcution_basic(world_t& world,int creature_num){
    if((int)world.creatures[creature_num].species->program[world.creatures[creature_num].programID-1].op <= 3) return true;
    return false;
}

std::string take_action(world_t& world,int creature_num){
    return "Creature (" + world.creatures[creature_num].species->name +" "+directName[world.creatures[creature_num].direction] + " "+std::to_string(world.creatures[creature_num].location.r) + " " + std::to_string(world.creatures[creature_num].location.c) + ") takes action: ";
}

void simulation_v(world_t& world){
    for(unsigned int j=0;j<world.numCreatures;j++){
        std::cout<<take_action(world,j)<<std::endl;
        while(!if_instrcution_basic(world,j)){
            if(world.creatures[j].species->program[world.creatures[j].programID-1].op == GO){
                instruction_ifgo(world,j);
                go(world,j);
            }
            else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == IFEMPTY){
                instruction_ifgo(world,j);
                ifempty(world,j);
            }
            else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == IFENEMY){
                instruction_ifgo(world,j);
                ifenemy(world,j);
            }
            else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == IFSAME){
                instruction_ifgo(world,j);
                ifsame(world,j);
            }
            else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == IFWALL){
                instruction_ifgo(world,j);
                ifwall(world,j);
            }
        }
        if(world.creatures[j].species->program[world.creatures[j].programID-1].op == LEFT){
            instruction_normal(world,j);
            left(world,j);
        }
        else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == RIGHT){
            instruction_normal(world,j);
            right(world,j);
        }
        else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == HOP){
            instruction_normal(world,j);
            hop(world,j);
        }
        else if(world.creatures[j].species->program[world.creatures[j].programID-1].op == INFECT){
            instruction_normal(world,j);
            infect(world,j);
        }
        print_world(world);
    }
}

void instruction_ifgo(world_t& world,int creature_num){
    std::cout<<"Instruction "<< world.creatures[creature_num].programID <<": "<<opName[world.creatures[creature_num].species->program[world.creatures[creature_num].programID-1].op]<<" "<<world.creatures[creature_num].species->program[world.creatures[creature_num].programID-1].address<<std::endl;
}

void instruction_normal(world_t& world,int creature_num){
    std::cout<<"Instruction "<< world.creatures[creature_num].programID <<": "<<opName[world.creatures[creature_num].species->program[world.creatures[creature_num].programID-1].op]<<std::endl;
}