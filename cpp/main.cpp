#include <iostream>

#include <memory>
#include <string>
#include <sstream>
#include "tcpserver.h"

#include <fstream>

const int PORT = 3331;

#include "DataManager.h"
#include "FilmObject.h"
#include "MultimediaObject.h"
#include "ObjectGroup.h"
#include "PhotoObject.h"
#include "VideoObject.h"

int main(int argc, const char* argv[]) {
    float chapterLengths[4]{2, 3, 1, 6};

    DataManager dataManager{};

    std::shared_ptr<ObjectGroup> objGroup = dataManager.addNewGroup("Test");

    objGroup->push_back(dataManager.addNewPhoto("TourEiffel", "../Data/TourEiffel.png"));
    objGroup->push_back(dataManager.addNewPhoto("Nadal", "../Data/Nadal.png"));
    objGroup->push_back(dataManager.addNewVideo("Ski", "../Data/Ski.mp4", 10));
    objGroup->push_back(dataManager.addNewFilm("Film", "../Data/Ski.mp4", 10, chapterLengths, 4));

    dataManager.print(std::cout);
 
    // Test serialization in a file
    std::ofstream file{"test.txt"};
    dataManager.serialize(file);
    file.close();

    std::cout << "\n\n-------------------\n";
    std::cout << "Deserialization\n\n";


    // Test deserialization from a file
    std::ifstream file2{"test.txt"};
    DataManager dataManager2{};

    dataManager2.deserialize(file2);
    file2.close();

    dataManager2.print(std::cout);

    std::cout << "\n\n-------------------\n\n";

    // cree le TCPServer
    auto* server = new TCPServer([&](std::string const& request, std::string& response) {
        // the request sent by the client to the server
        std::cout << "request: " << request << std::endl;

        std::stringstream ss{request};

        std::string command {};  
        ss >> command;

        // The rest is the name of the object
        std::string name {};
        std::getline(ss, name);
        name.erase(0, 1);

        // For each command, we check if the object exists and then execute the command, and return the result in the response string
        if(command == "display") {
            if(dataManager.getObject(name) != nullptr) {
                std::stringstream stream{};
                dataManager.printObject(name, stream);
                response = stream.str();
            } else {
                response = "Object not found : " + name;
            }
        } else if(command == "play") {
            if(dataManager.getObject(name) != nullptr) {
                dataManager.playObject(name);
                response = "Playing object : " + name;
            } else {
                response = "Object not found : " + name;
            }
        } else if(command == "list") {
            std::stringstream stream{};
            dataManager.listNames(stream);
            response = stream.str();
        } else {
            response = "Unknown command : " + command;
        }

        // return false would close the connection with the client
        return true;
    });

    std::cout << "Starting Server on port " << PORT << std::endl;

    int status = server->run(PORT);

    if (status < 0) {
        std::cerr << "Could not start Server on port " << PORT << std::endl;
        return 1;
    }

    return 0;
}