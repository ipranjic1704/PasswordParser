#pragma once
#include "PasswordRecord.h"
#include <string>
#include <vector>

// Odgovornost: iz retka zaglavlja odrediti koji stupac nosi koje logicko
// polje (name/url/username/password/note), mapiranjem PO IMENU umjesto po
// poziciji. Tako radi za razlicite izvoznike (Comet, 1Password, Bitwarden,
// LastPass, Firefox...) jer prepoznaje nazive stupaca i njihove aliase.
class ColumnMapper {
public:
    // Izgradi mapiranje iz retka zaglavlja. Ako ne prepozna nijedan stupac,
    // pada natrag na Chromium pozicijski raspored (0..4).
    explicit ColumnMapper(const std::vector<std::string>& header);

    // Pretvori redak podataka u zapis prema otkrivenom mapiranju.
    // Nedostajuci stupci ostaju prazni (bez pada).
    PasswordRecord toRecord(const std::vector<std::string>& row) const;

private:
    int nameIdx_ = -1;
    int urlIdx_ = -1;
    int usernameIdx_ = -1;
    int passwordIdx_ = -1;
    int noteIdx_ = -1;

    // Normalizira naziv zaglavlja (mala slova, obrezani razmaci) radi usporedbe.
    static std::string normalize(const std::string& s);

    // Sigurno dohvati polje po indeksu -> "" ako indeks ne postoji.
    static std::string fieldAt(const std::vector<std::string>& row, int idx);
};
