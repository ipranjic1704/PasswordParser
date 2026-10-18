#include "CsvParser.h"
#include "ColumnMapper.h"

std::vector<std::vector<std::string>>
CsvParser::tokenize(const std::string& content) const {
    std::vector<std::vector<std::string>> rows;
    std::vector<std::string> current;
    std::string field;
    bool inQuotes = false;

    std::size_t i = 0;
    const std::size_t n = content.size();

    // Preskoci UTF-8 BOM (EF BB BF) ako postoji na pocetku.
    if (n >= 3 &&
        static_cast<unsigned char>(content[0]) == 0xEF &&
        static_cast<unsigned char>(content[1]) == 0xBB &&
        static_cast<unsigned char>(content[2]) == 0xBF) {
        i = 3;
    }

    for (; i < n; ++i) {
        const char c = content[i];

        if (inQuotes) {
            if (c == '"') {
                // "" unutar navodnika = jedan doslovni navodnik.
                if (i + 1 < n && content[i + 1] == '"') {
                    field += '"';
                    ++i;
                } else {
                    inQuotes = false; // kraj citiranog dijela
                }
            } else {
                field += c; // zarez / novi red unutar navodnika je doslovan
            }
        } else {
            if (c == '"') {
                inQuotes = true;
            } else if (c == ',') {
                current.push_back(field);
                field.clear();
            } else if (c == '\r') {
                // dio CRLF-a -- ignoriramo, split radi \n
            } else if (c == '\n') {
                current.push_back(field);
                field.clear();
                rows.push_back(current);
                current.clear();
            } else {
                field += c;
            }
        }
    }

    // Zadnji redak ako datoteka ne zavrsava novim redom.
    if (!field.empty() || !current.empty()) {
        current.push_back(field);
        rows.push_back(current);
    }

    return rows;
}

std::vector<PasswordRecord>
CsvParser::parse(const std::string& content) const {
    std::vector<PasswordRecord> records;
    const auto rows = tokenize(content);
    if (rows.empty()) return records;

    // Prvi redak = zaglavlje -> odreduje gdje je koji stupac.
    const ColumnMapper mapper(rows.front());

    // Ostali redci = podaci.
    for (std::size_t i = 1; i < rows.size(); ++i) {
        records.push_back(mapper.toRecord(rows[i]));
    }
    return records;
}
