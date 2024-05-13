#ifndef VIDEOOBJECT_H
#define VIDEOOBJECT_H

#include "MultimediaObject.h"
class VideoObject : public MultimediaObject {
private:
	float length{};

public:
	VideoObject() : MultimediaObject() {}
	VideoObject(std::string name, std::string pathname) : MultimediaObject(name, pathname) {}
	VideoObject(std::string name, std::string pathname, float length) : MultimediaObject(name, pathname) { this->length = length; };

public:
	float getLength() const { return length; }
	void setLenght(float length) { this->length = length; }

public:
	void print(std::ostream& os) const override {
		os << "Video object (name = \"" << getName() << "\", pathname = \"" << getPathname() << "\", length=" << getLength() << ")";
	};
	const void play() override {
		std::string command = "mpv \"" + getPathname() + "\" &";
		system(command.c_str());
	}

	void serialize(std::ostream& os) const override {
		os << "Video ";
		MultimediaObject::serialize(os);
		os << length << ";";
	}

	void serializeWithoutType(std::ostream& os) const {
		MultimediaObject::serialize(os);
		os << length << ";";
	}

	void deserialize(std::istream& is) override {
		MultimediaObject::deserialize(is);
		std::string lengthStr;
		std::getline(is, lengthStr, ';');
		length = std::stof(lengthStr);
	}
};

#endif // VIDEOOBJECT_H