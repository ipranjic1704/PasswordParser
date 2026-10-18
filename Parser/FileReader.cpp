#include "FileReader.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>

std::string FileReader::readAll(const std::string& path) const {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw FileReadException("Ne mogu otvoriti datoteku: " + path);
    }
    std::ostringstream buffer;
    buffer << in.rdbuf();
    if (in.bad()) {
        throw FileReadException("Greska pri citanju datoteke: " + path);
    }
    return buffer.str();
}
