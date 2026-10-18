#pragma once
#include "PasswordRecord.h"
#include <string>
#include <vector>

// Odgovornost: pretvoriti sirovi tekst CSV-a u zapise.
// Sintaksu CSV-a rjesava tokenizator (navodnici, zarezi, novi redovi),
// a KOJI stupac je KOJE polje prepusta ColumnMapper-u (mapiranje po imenu).
// Tolerantan je -- krnji redci ne rusе program, samo daju prazna polja.
class CsvParser {
public:
    // Parsira sadrzaj: prvi redak je zaglavlje (odreduje mapiranje stupaca),
    // ostali su podaci. Nikada ne baca iznimku na losem sadrzaju.
    std::vector<PasswordRecord> parse(const std::string& content) const;

private:
    // Tokenizator: razbija cijeli tekst u retke, a retke u polja,
    // postujuci navodnike. Srce ispravnog CSV parsiranja.
    std::vector<std::vector<std::string>> tokenize(const std::string& content) const;
};
