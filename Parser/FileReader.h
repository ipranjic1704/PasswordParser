#pragma once
#include <string>

// Odgovornost: procitati cijeli sadrzaj tekstualne datoteke u string.
// Ne zna nista o CSV-u -- samo o datotekama.
class FileReader {
public:
    // Vraca cijeli sadrzaj datoteke. Baca FileReadException ako ne uspije.
    std::string readAll(const std::string& path) const;
};
