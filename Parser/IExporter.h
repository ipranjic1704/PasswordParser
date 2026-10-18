#pragma once
#include "PasswordRecord.h"
#include <string>
#include <vector>

// SUCELJE (apstraktna klasa): ugovor za svaki izvoznik.
// Application ovisi o ovoj apstrakciji, ne o konkretnim formatima
// (Dependency Inversion). Novi format = nova izvedena klasa.
class IExporter {
public:
    virtual ~IExporter() = default;

    // Zapise zapise na danu putanju. Baca ExportException pri neuspjehu.
    virtual void exportTo(const std::vector<PasswordRecord>& records,
                          const std::string& path) const = 0;

    // Zadano ime izlazne datoteke za ovaj format (npr. "lozinke.html").
    virtual std::string defaultFileName() const = 0;
};
