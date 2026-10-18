#pragma once
#include "IExporter.h"

// Izvoz natrag u CSV (ispravno escapea polja -> otvara se u Excelu).
class CsvExporter : public IExporter {
public:
    void exportTo(const std::vector<PasswordRecord>& records,
                  const std::string& path) const override;
    std::string defaultFileName() const override { return "lozinke.csv"; }

private:
    // Oklopi polje navodnicima ako sadrzi , " ili novi red.
    static std::string escapeField(const std::string& s);
};
