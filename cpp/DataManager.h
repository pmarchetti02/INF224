#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <map>
#include <string>
#include <memory>

#include "MultimediaObject.h"
#include "ObjectGroup.h"

#include "PhotoObject.h"
#include "VideoObject.h"
#include "FilmObject.h"

typedef std::map<std::string, std::shared_ptr<MultimediaObject>> ObjectMap;
typedef std::map<std::string, std::shared_ptr<ObjectGroup>> GroupMap;

class DataManager {
private:
    ObjectMap multimediaObjects {};
    GroupMap groups {};
public:
    /*
    These methods (addNew*) return a shared_ptr to the created object that will be stored in the map, and nullptr if an object with the same name already exists.
    */
    std::shared_ptr<PhotoObject> addNewPhoto(std::string name, std::string pathname, int width = 0, int height = 0) {
        if(getObject(name)) {
            std::cerr << "Object with name " << name << " already exists\n";
            return nullptr;
        }
        std::shared_ptr<PhotoObject> obj {new PhotoObject(name, pathname, width, height) };
        multimediaObjects[name] = obj;
        return obj;
    }
    std::shared_ptr<VideoObject> addNewVideo(std::string name, std::string pathname, float length) {
        if(getObject(name)) {
            std::cerr << "Object with name " << name << " already exists\n";
            return nullptr;
        }
        std::shared_ptr<VideoObject> obj = std::make_shared<VideoObject>(name, pathname, length);
        multimediaObjects[name] = obj;
        return obj;
    }
    std::shared_ptr<FilmObject> addNewFilm(std::string name, std::string pathname, float length, float *chapters, int nChapters) {
        if(getObject(name)) {
            std::cerr << "Object with name " << name << " already exists\n";
            return nullptr;
        }
        std::shared_ptr<FilmObject> obj = std::make_shared<FilmObject>(name, pathname, length, chapters, nChapters);
        multimediaObjects[name] = obj;
        return obj;
    }
    std::shared_ptr<ObjectGroup> addNewGroup(std::string name) {
        if(getObject(name)) {
            std::cerr << "Group with name " << name << " already exists\n";
            return nullptr;
        }
        std::shared_ptr<ObjectGroup> obj = std::make_shared<ObjectGroup>(name);
        groups[name] = obj;
        return obj;
    }

    /*
        This method returns a shared_ptr to the existing object that was added, and nullptr if an object with the same name already exists.
    */
    std::shared_ptr<MultimediaObject> addObject(std::shared_ptr<MultimediaObject> obj) {
        if(getObject(obj->getName())) {
            std::cerr << "Object with name " << obj->getName() << " already exists\n";
            return nullptr;
        }
        multimediaObjects[obj->getName()] = obj;
        return obj;
    }

    /*
        This method returns seeks for an object with the given name in the map, and returns a shared_ptr to it if it exists, and nullptr otherwise.
    */
    std::shared_ptr<MultimediaObject> getObject(std::string name) {
        auto it = multimediaObjects.find(name);
        if (it != multimediaObjects.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    /*
        this methods seeks for an object or a group with the given name in the map, and prints it if it exists, and prints an error message otherwise.
    */
    void printObject(std::string name, std::ostream& os) {
        auto itObj = multimediaObjects.find(name);
        auto itGroup = groups.find(name);
        if (itObj != multimediaObjects.end()) itObj->second->print(os);
        else if (itGroup != groups.end()) itGroup->second->print(os);
        else std::cerr << "Object not found : " << name << "\n";
    }

    /*
        this methods seeks for an object or a group with the given name in the map, and prints it if it exists, and plays an error message otherwise.
    */
    void playObject(std::string name) {
        auto it = multimediaObjects.find(name);
        if (it != multimediaObjects.end()) {
            it->second->play();
        } else {
            std::cerr << "Object not found : " << name << "\n";
        }
    }

    /*
        this methods seeks for an object or a group with the given name in the map, and deletes it if it exists, and prints an error message otherwise.
    */
    void deleteObject(std::string name) {
        auto it = multimediaObjects.find(name);
        if (it != multimediaObjects.end()) {
            multimediaObjects.erase(it);
        } else {
            std::cerr << "Object not found : " << name << "\n";
        }
    }

    /*
        This method prints all the objects and groups in the map.
    */
    void print(std::ostream& os) {
        os << "Multimedia objects : ";
        for (auto it = multimediaObjects.begin(); it != multimediaObjects.end(); it++) {
            it->second->print(os);
            os << ", ";
        }
        os << ";";
        os << "Groups : ";
        for (auto it = groups.begin(); it != groups.end(); it++) {
            it->second->print(os);
            os << ", ";
        }
    }

    /*
        This method serializes all the objects in the map. Groups are not supported yet.
    */
    void serialize(std::ostream& os) {
        os << multimediaObjects.size() << " ";
        for (auto it = multimediaObjects.begin(); it != multimediaObjects.end(); it++) {
            it->second->serialize(os);
        }
    }

    /*
        This method fills the DataManager with serialized objects from a stream. Groups are not supported yet.
    */
    void deserialize(std::istream& is) {
        int nObjects;
        is >> nObjects;
        for (int i = 0; i < nObjects; i++) {
            std::string objType;
            is >> objType;

            std::shared_ptr<MultimediaObject> obj;
            if (objType == "Photo") {
                obj = std::make_shared<PhotoObject>("", "", 0, 0);
            } else if (objType == "Video") {
                obj = std::make_shared<VideoObject>("", "", 0);
            } else if (objType == "Film") {
                obj = std::make_shared<FilmObject>("", "", 0, nullptr, 0);
            } else {
                std::cerr << "Unknown object type : " << objType << "\n";
                return;
            }

            obj->deserialize(is);
            addObject(obj);
        }
    }
    /*
        This method gets the names of all the objects and groups in the map.
    */
    void listNames(std::ostream& os) {
        os << "Multimedia objects : ";
        for (auto it = multimediaObjects.begin(); it != multimediaObjects.end(); it++) {
            os << it->first << ", ";
        }
        os << "Groups : ";
        for (auto it = groups.begin(); it != groups.end(); it++) {
            os << it->first << ", ";
        }
    }
};

#endif // DATA_MANAGER_H