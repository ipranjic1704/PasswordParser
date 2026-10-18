#pragma once
#include "IExporter.h"

// Izvoz u HTML tablicu. Word i Excel je oba otvaraju kao dokument/tablicu.
class HtmlExporter : public IExporter {
public:
    void exportTo(const std::vector<PasswordRecord>& records,
                  const std::string& path) const override;
    std::string defaultFileName() const override { return "lozinke.html"; }

private:
    // Escapea posebne HTML znakove (<, >, &, ") da ne razbiju tablicu.
    static std::string escapeHtml(const std::string& s);
};
