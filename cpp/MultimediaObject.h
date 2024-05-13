#ifndef MULTIMEDIA_OBJECT_H
#define MULTIMEDIA_OBJECT_H

#include <memory>

#include <string>
#include <iostream>

class MultimediaObject {
private: // Attributes
	std::string name{};
	std::string pathname{};

public: // Constructors and destructors
	MultimediaObject() {}
	MultimediaObject(std::string name, std::string pathname) {
		this->name = name;
		this->pathname = pathname;
	}

	virtual ~MultimediaObject() {
	}

public: // Getters and setters
	std::string getName() const { return name; };
	std::string getPathname() const { return pathname; };

	void setName(std::string name) { this->name = name; }
	void setPathname(std::string pathname) { this->pathname = pathname; };

public: // Other functions
	virtual void print(std::ostream& os) const {
		os << "Multimedia object (Name = \"" << name << "\", Pathname = \"" << pathname << "\");";
	};
	virtual const void play() = 0;

	virtual void serialize(std::ostream& os) const {
		os << name << ";" << pathname << ";";
	};

	virtual void deserialize(std::istream& is) {
		std::getline(is, name, ';');
		std::getline(is, pathname, ';');
	};
};

typedef std::shared_ptr<MultimediaObject> DataPtr;

#endif