#include "FilmObject.h"

FilmObject& FilmObject::operator=(const FilmObject& from) {
	this->setPathname(from.getPathname());
	this->setName(from.getName());
	this->setLenght(from.getLength());
	this->setChapterLengths(from.getChapterLengths(), from.getNumChapters());

	return *this;
}
