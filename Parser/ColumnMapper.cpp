#include "ColumnMapper.h"
#include <algorithm>
#include <cctype>

std::string ColumnMapper::normalize(const std::string& s) {
    std::size_t begin = 0;
    std::size_t end = s.size();
    while (begin < end && std::isspace(static_cast<unsigned char>(s[begin]))) ++begin;
    while (end > begin && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;

    std::string out;
    out.reserve(end - begin);
    for (std::size_t i = begin; i < end; ++i) {
        out += static_cast<char>(std::tolower(static_cast<unsigned char>(s[i])));
    }
    return out;
}

std::string ColumnMapper::fieldAt(const std::vector<std::string>& row, int idx) {
    if (idx < 0 || static_cast<std::size_t>(idx) >= row.size()) return "";
    return row[idx];
}

ColumnMapper::ColumnMapper(const std::vector<std::string>& header) {
    // Aliasi naziva stupaca po menadzerima. Prvi pogodak za svako polje
    // se zadrzava (ne prepisujemo vec postavljeno).
    for (std::size_t i = 0; i < header.size(); ++i) {
        const std::string h = normalize(header[i]);
        const int idx = static_cast<int>(i);

        if (nameIdx_ < 0 &&
            (h == "name" || h == "title" || h == "item" || h == "account")) {
            nameIdx_ = idx;
        } else if (urlIdx_ < 0 &&
            (h == "url" || h == "uri" || h == "website" || h == "web site" ||
             h == "login_uri" || h == "login_url" || h == "site")) {
            urlIdx_ = idx;
        } else if (usernameIdx_ < 0 &&
            (h == "username" || h == "user" || h == "user name" ||
             h == "login_username" || h == "login name" ||
             h == "email" || h == "e-mail")) {
            usernameIdx_ = idx;
        } else if (passwordIdx_ < 0 &&
            (h == "password" || h == "pass" || h == "pwd" ||
             h == "login_password")) {
            passwordIdx_ = idx;
        } else if (noteIdx_ < 0 &&
            (h == "note" || h == "notes" || h == "extra" ||
             h == "comment" || h == "comments")) {
            noteIdx_ = idx;
        }
    }

    // Nijedan prepoznat stupac -> datoteka vjerojatno nema (poznato) zaglavlje.
    // Padni na Chromium pozicijski raspored: name,url,username,password,note.
    if (nameIdx_ < 0 && urlIdx_ < 0 && usernameIdx_ < 0 &&
        passwordIdx_ < 0 && noteIdx_ < 0) {
        nameIdx_ = 0;
        urlIdx_ = 1;
        usernameIdx_ = 2;
        passwordIdx_ = 3;
        noteIdx_ = 4;
    }
}

PasswordRecord ColumnMapper::toRecord(const std::vector<std::string>& row) const {
    PasswordRecord r;
    r.name = fieldAt(row, nameIdx_);
    r.url = fieldAt(row, urlIdx_);
    r.username = fieldAt(row, usernameIdx_);
    r.password = fieldAt(row, passwordIdx_);
    r.note = fieldAt(row, noteIdx_);
    return r;
}
