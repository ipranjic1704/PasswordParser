#pragma once
#include <string>

// MODEL: jedan zapis lozinke. Jedina odgovornost -> drzati podatke jednog
// retka i znati procijeniti je li vrijedan izvoza (isValid).
// Popunjavanje polja iz CSV-a radi ColumnMapper (mapiranje po imenu stupca).
class PasswordRecord {
public:
    std::string name;
    std::string url;
    std::string username;
    std::string password;
    std::string note;

    // -----------------------------------------------------------------------
    // TODO (TVOJA ODLUKA): sto cini zapis "vrijednim" izvoza?
    //
    // Ovo je poslovno pravilo, ne mehanika -- zato ga ostavljam tebi.
    // Application ce preskociti svaki zapis za koji ovo vrati false.
    //
    // Razmisli o kompromisima:
    //   - Odbaciti potpuno prazne retke? (gotovo sigurno da)
    //   - Zahtijevati barem korisnicko ime ILI lozinku?
    //   - Zahtijevati i URL? (mozda prestrogo -- neke stavke su samo biljeske)
    //
    // Trenutno: prihvaca sve osim potpuno praznog zapisa. Prilagodi po zelji.
    // -----------------------------------------------------------------------
    bool isValid() const {
        return !(name.empty() && url.empty() && username.empty()
                 && password.empty() && note.empty());
    }
};
