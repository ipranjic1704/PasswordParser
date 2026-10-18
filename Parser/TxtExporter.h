#pragma once
#include "IExporter.h"

// Izvoz u obicni tekst (citljivo, jedan blok po zapisu).
class TxtExporter : public IExporter {
public:
    void exportTo(const std::vector<PasswordRecord>& records,
                  const std::string& path) const override;
    std::string defaultFileName() const override { return "lozinke.txt"; }
};
