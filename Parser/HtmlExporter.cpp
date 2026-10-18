#include "HtmlExporter.h"
#include "Exceptions.h"
#include <fstream>

std::string HtmlExporter::escapeHtml(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        switch (c) {
            case '&': out += "&amp;";  break;
            case '<': out += "&lt;";   break;
            case '>': out += "&gt;";   break;
            case '"': out += "&quot;"; break;
            default:  out += c;
        }
    }
    return out;
}

void HtmlExporter::exportTo(const std::vector<PasswordRecord>& records,
                            const std::string& path) const {
    std::ofstream out(path);
    if (!out) {
        throw ExportException("Ne mogu stvoriti datoteku: " + path);
    }

    out << "<!DOCTYPE html>\n<html lang=\"hr\">\n<head>\n"
        << "<meta charset=\"UTF-8\">\n<title>Izvezene lozinke</title>\n"
        << "<style>"
        << "table{border-collapse:collapse;font-family:sans-serif}"
        << "th,td{border:1px solid #888;padding:6px 10px;text-align:left}"
        << "th{background:#f0f0f0}"
        << "</style>\n</head>\n<body>\n"
        << "<h1>Izvezene lozinke</h1>\n<table>\n"
        << "<tr><th>Naziv</th><th>URL</th><th>Korisnik</th>"
        << "<th>Lozinka</th><th>Napomena</th></tr>\n";

    for (const auto& r : records) {
        out << "<tr><td>" << escapeHtml(r.name)
            << "</td><td>" << escapeHtml(r.url)
            << "</td><td>" << escapeHtml(r.username)
            << "</td><td>" << escapeHtml(r.password)
            << "</td><td>" << escapeHtml(r.note)
            << "</td></tr>\n";
    }

    out << "</table>\n</body>\n</html>\n";
}
