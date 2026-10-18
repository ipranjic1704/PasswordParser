#include "CsvExporter.h"
#include "Exceptions.h"
#include <fstream>

std::string CsvExporter::escapeField(const std::string& s) {
    const bool needsQuotes =
        s.find(',') != std::string::npos ||
        s.find('"') != std::string::npos ||
        s.find('\n') != std::string::npos ||
        s.find('\r') != std::string::npos;

    if (!needsQuotes) return s;

    std::string out = "\"";
    for (char c : s) {
        if (c == '"') out += "\"\""; // udvostruci navodnike
        else out += c;
    }
    out += "\"";
    return out;
}

void CsvExporter::exportTo(const std::vector<PasswordRecord>& records,
                           const std::string& path) const {
    std::ofstream out(path);
    if (!out) {
        throw ExportException("Ne mogu stvoriti datoteku: " + path);
    }
    out << "name,url,username,password,note\n";
    for (const auto& r : records) {
        out << escapeField(r.name)     << ','
            << escapeField(r.url)      << ','
            << escapeField(r.username) << ','
            << escapeField(r.password) << ','
            << escapeField(r.note)     << '\n';
    }
}
