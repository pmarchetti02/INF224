#include "ObjectGroup.h"

void ObjectGroup::print(std::ostream& os) const {
	std::cout << "Object group : [";
	for (DataPtr data : *this) {
		std::cout << " | "; data->print(os);
	}
	std::cout << " ]";
}
