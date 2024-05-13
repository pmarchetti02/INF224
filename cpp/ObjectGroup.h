#ifndef OBJECT_GROUP_H
#define OBJECT_GROUP_H

#include <list>
#include "MultimediaObject.h"

class ObjectGroup : public std::list<DataPtr> {

private:
	const std::string name;
public: // Constructeurs
	ObjectGroup() : std::list<DataPtr>() {}
	ObjectGroup(std::string name) : std::list<DataPtr>(), name(name) { };

public: // Setters et getters
	std::string const getName() const { return name; };

public: // Autres m�thodes
	void print(std::ostream& os) const;
};

#endif