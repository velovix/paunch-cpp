#include "paunch.h"

namespace paunch {

Error::Error(std::string message) {

	this->message = message;
}

std::string Error::Report() {

	return this->message;
}

}
