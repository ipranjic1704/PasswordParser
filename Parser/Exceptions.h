#pragma once
#include <stdexcept>
#include <string>

// Zajednicka osnova za sve greske aplikacije. Omogucuje da Application
// uhvati bilo koju nasu gresku jednim catch-om, a i dalje razlikuje tipove.
class AppException : public std::runtime_error {
public:
    explicit AppException(const std::string& msg) : std::runtime_error(msg) {}
};

// Greska pri citanju ulazne datoteke (ne postoji, nema dozvole, ...).
class FileReadException : public AppException {
public:
    explicit FileReadException(const std::string& msg) : AppException(msg) {}
};

// Greska pri zapisu izlazne datoteke.
class ExportException : public AppException {
public:
    explicit ExportException(const std::string& msg) : AppException(msg) {}
};
