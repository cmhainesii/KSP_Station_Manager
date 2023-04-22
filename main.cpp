#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include <ios>
#include <cxxopts.hpp>

#include <nlohmann/json.hpp>
#include <fmt/core.h>

#include "include/space_station.hpp"
#include "include/menu.hpp"
#include "include/celestial_body.hpp"
#include "include/build_vars.h"
#include "include/station_list.hpp"

using SpaceStation = KSP_SM::SpaceStationBuilder::SpaceStation;
using SpaceStationBuilder = KSP_SM::SpaceStationBuilder;

using nlohmann::json;
using std::vector;
using namespace KSP_SM;

using unique_station = std::unique_ptr<SpaceStation>;

int main(int argc, char **argv);

const string STATIONS_FILENAME = "stations.json";

int main(int argc, char **argv)
{
    /*
    // Convert arguments list to a vector of std::strings
    vector<string> argument_list(argv, argv + argc);

    if (argument_list.size() >= 2)
    {
        string output_filename {"stations.txt"};
        std::cout << "fn: " << output_filename << "\n";
        // Running in non-interactive mode!
        if(argument_list.at(1).compare("-i") == 0)
        {
            // If filename supplied in cmd line args, use it.
            if (argument_list.size() >=3)
            {
                output_filename = argument_list.at(2);
            }

            // Create and populate stations list from stations.json
            StationList stations;
            auto num_stations = stations.ReadStationsFromFile(STATIONS_FILENAME);
            
            // No stations found in station.json
            if(!num_stations)
            {
                std::cout << "No stations\n";
                return 0;
            }

            // Attempt to open file and write station info in plain text
            try {            
                std::ofstream out_file(output_filename);
                out_file.exceptions(std::ofstream::failbit);
                for (const auto& current : stations.GetStations())
                {
                    out_file << current->ToString();
                }
            } catch (const std::ofstream::failure& e)
            {
                std::cerr << "Error opening file for writing.\n";
                std::cerr << e.what() << '\n';
                return -1;
            }
        }

        return 0;
    }
    */
   cxxopts::Options options("MyProgram", "One line description");

   options.add_options()
    ("d,dump", "Dump Station Info To Text File") // Bool parameter
    ("o,outfile", "Output Filename", cxxopts::value<string>()->default_value("stations.txt"))
    ("i,infile", "Stations JSON Input Filename", cxxopts::value<string>()->default_value("stations.json"))
    ;
    
    string out_filename {};
    try{
        auto result = options.parse(argc,argv);
        
        if (result.count("dump"))
        {
            // Outputting station info to text file
            out_filename = result["outfile"].as<string>();
            string in_filename = result["infile"].as<string>();
            std::cout << fmt::format("Output filename: {}\n", out_filename);
            std::cout << fmt::format("Input filename: {}\n", in_filename);

            StationList stations;
            stations.ReadStationsFromFile(in_filename);
            std::ofstream out_file(out_filename);
            out_file.exceptions(std::ofstream::failbit);
            for (const auto& current : stations.GetStations())
            {
                out_file << current->ToString();
            }
            return EXIT_SUCCESS;
        }
    } catch (const cxxopts::exceptions::parsing& e)
    {
        std::cerr << "Caught\n";
        std::cerr << fmt::format("Error: {}\n", e.what());
        return EXIT_FAILURE;
    } catch (std::ofstream::failure& e)
    {
        std::cerr << fmt::format("Error opening file: {} for writing. Aborting.\n", out_filename);
        return EXIT_FAILURE;
    }

    

   

    StationList stations;
    bool exitProgram = false;
    std::string buffer;
    std::string menuText = Menu::GetMainMenuText();

    std::cout << "KSP Station Manger\n";
    std::cout << fmt::format("Verson: {}.{}\n", KSP_SM_VERSION_MAJOR, KSP_SM_VERSION_MINOR);

    while (!exitProgram)
    {

        std::cout << std::endl;
        std::cout << menuText;
        std::cout << "Enter Your Selection: ";
        std::cin >> buffer;
        if(buffer.size() == 0 )
        {
            continue;
        }
        char selection = std::tolower(buffer.at(0));
        if (selection == 'r')
        {
            // Attempt to read stations from file. Result is the number of stations read from json file.
            auto number_of_stations = stations.ReadStationsFromFile(STATIONS_FILENAME);
            if (!number_of_stations) // Show an error if no stations are found / file not found.
            {
                std::cerr << "Aborting." << std::endl;
                continue;
            }
            // Successful load, print number of stations loaded and go back to the main menu.
            std::cout << fmt::format("Read in {} stations from file {}.", stations.GetSize(), STATIONS_FILENAME) << std::endl;
            continue;
        }
        if (selection == 'w')
        {
            stations.WriteStationsToFile(STATIONS_FILENAME);

            std::cout << "Wrote stations list to file." << std::endl
                      << std::endl;
            continue;
        }
        if (selection == 'a')
        {
            auto newStation = SpaceStationBuilder::createStationFromConsoleInput();
            stations.AddStation(newStation);
            continue;
        }
        if (selection == 'd')
        {
            std::size_t station_index;
            std::cout << std::endl;
            std::cout << "Delete Station" << std::endl;
            std::cout << "Enter Station List Index: ";
            while (!(std::cin >> station_index))
            {
                std::cout << "Invalid Index" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Station List Index: ";
            }

            if (stations.DeleteStation(station_index))
            {
                std::cout << fmt::format("Deleted station at index {}", station_index) << std::endl;
            }
            else
            {
                std::cout << "Invalid index / Station not found" << std::endl;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (selection == 'l')
        {
            stations.ListAllStations();
            continue;
        }

        if (selection == 'm')
        {
            stations.ManageStationsFromConsole();
            continue;
        }
        if (selection == 'q')
        {
            exitProgram = true;
            continue;
        }

        std::cerr << "Error reading selection." << std::endl;
    }

    return 0;
}
