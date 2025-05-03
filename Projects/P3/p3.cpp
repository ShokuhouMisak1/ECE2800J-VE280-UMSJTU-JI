#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include"world_type.h"
#include"simulation.h"

int main(int argc, char* argv[]){
    if(argc <= 3) {
        std::cout<< "Error: Missing arguments! "<<std::endl<<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose] ";
        exit(0);
    }
    if(atoi(argv[3])<0) {
        std::cout<<"Error: Number of simulation rounds is negative! ";
        exit(0);
    }
    for(int i=1;i<3;i++){
        if(!if_file_open_successful(argv[i])){
            std::cout<<"Error: Cannot open file "<<argv[i]<<"! ";
            exit(0);
        }
    }
    //0. Realize Program Arguments
    if(!if_exceed_max(argv[1],MAXSPECIES+1)){
        std::cout<<"Error: Too many species! "<<std::endl<<"Maximal number of species is "<<MAXSPECIES<<". ";
        exit(0);
    }
    world_t world;
    std::ifstream ifile(argv[1]);
    initialize_species(world,ifile);
    ifile.close();
    //2.read the species summary file and the programs for all the species
    ifile.open(argv[2]);
    std::string world_per_line;
    initial_grid(world,ifile);
    initial_creature(world,ifile);
    std::cout<<"Initial state"<<std::endl;
    print_world(world);
    if(argc == 4){
        for(int i=1;i<=atoi(argv[3]);i++){
            std::cout<<"Round "<<i<<" "<<std::endl;
            simulation_concise(world);
            print_world(world);
        }
    }
    if(argc >= 5){
        std::string mode = argv[4];
        if(mode != "v" && mode !="verbose"){
            for(int i=1;i<=atoi(argv[3]);i++){
                std::cout<<"Round "<<i<<" "<<std::endl;
                simulation_concise(world);
                print_world(world);
            }
        }
        else{
            for(int i=1;i<=atoi(argv[3]);i++){
                std::cout<<"Round "<<i<<" "<<std::endl;
                simulation_v(world);
            }
        }
    }
    return 0;
}