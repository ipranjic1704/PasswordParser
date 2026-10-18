#include "TxtExporter.h"
#include "Exceptions.h"
#include <fstream>

void TxtExporter::exportTo(const std::vector<PasswordRecord>& records,
                           const std::string& path) const {
    std::ofstream out(path);
    if (!out) {
        throw ExportException("Ne mogu stvoriti datoteku: " + path);
    }
    for (const auto& r : records) {
        out << "Naziv:    " << r.name << "\n"
            << "URL:      " << r.url << "\n"
            << "Korisnik: " << r.username << "\n"
            << "Lozinka:  " << r.password << "\n"
            << "Napomena: " << r.note << "\n"
            << "----------------------------------------\n";
    }
}
