#ifndef FILM_OBJECT_H
#define FILM_OBJECT_H

#include "VideoObject.h"

class FilmObject : public VideoObject {
private:
	float* chapterLengths {};
	int numChapters{};

public: // Constructors
	FilmObject() : VideoObject() {}
	FilmObject(std::string name, std::string pathname) : VideoObject(name, pathname) {}
	FilmObject(std::string name, std::string pathname, float length) : VideoObject(name, pathname, length) {}
	FilmObject(std::string name, std::string pathname, float length, float* chapterLengths, int numChapters)
		: VideoObject(name, pathname, length) {
			setChapterLengths(chapterLengths, numChapters);
	}

public: // Getters et setters

	float* const getChapterLengths() const { return chapterLengths; }
	int getNumChapters() const { return numChapters; }

	void setChapterLengths(float* chapterLengths, int numChapters) {
		if (chapterLengths != nullptr) delete[] this->chapterLengths;
		this->chapterLengths = new float[numChapters]();
		this->numChapters = numChapters;
		if (this->chapterLengths && chapterLengths) {
			for (int i = 0; i < numChapters; i++) {
				this->chapterLengths[i] = chapterLengths[i];
			}
		} else {
			if (chapterLengths != nullptr) delete[] this->chapterLengths;
			this->numChapters = 0;
		}
	}

	void setNumChapters(int numChapters) { this->numChapters = numChapters; }

public: // Opérateurs de copie
	FilmObject(const FilmObject &from) : FilmObject(from.getPathname(), from.getName(), from.getLength(), from.getChapterLengths(), from.getNumChapters()) { }
	
	FilmObject& operator=(const FilmObject& from);


public: // Autres méthodes

	void print(std::ostream& os) const override {
		os << "Film object (name = \"" << getName() << "\", pathname = \"" << getPathname() << "\", length=" << getLength() << ",";
		os << "Chapter lengths : [";
		for (int i = 0; i < numChapters; i++) {
			os << " " << chapterLengths[i] << "seconds ,";
		}
		os << "])";
	}

	~FilmObject() {
		if (chapterLengths != nullptr)
			delete[] this->chapterLengths;
	}

	virtual void serialize(std::ostream& os) const override {
		os << "Film ";
		VideoObject::serializeWithoutType(os);
		os << numChapters << ";";
		for (int i = 0; i < numChapters; i++) {
			os << chapterLengths[i] << ";";
		}
	}

	virtual void deserialize(std::istream& is) override {
		VideoObject::deserialize(is);
		std::string numChaptersStr;
		std::getline(is, numChaptersStr, ';');
		numChapters = std::stoi(numChaptersStr);
		chapterLengths = new float[numChapters]();
		for (int i = 0; i < numChapters; i++) {
			std::string chapterLengthStr;
			std::getline(is, chapterLengthStr, ';');
			chapterLengths[i] = std::stof(chapterLengthStr);
		}
	}
};

#endif // !FILM_OBJECT_H
