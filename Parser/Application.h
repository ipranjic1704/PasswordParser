#pragma once
#include "OutputFormat.h"
#include <string>

// Orkestrator: povezuje citanje, parsiranje, odabir formata i izvoz.
// Sama po sebi ne zna detalje nijednog koraka -- samo redoslijed.
// Svojom metodom run() jamci da aplikacija ne pukne, sto god se dogodi.
class Application {
public:
    // Pokrece cijeli tijek. Vraca izlazni kod procesa (0 = uspjeh).
    int run();

private:
    // Interakcija s korisnikom (jedina mjesta koja dodiruju cin/cout).
    std::string askInputPath() const;
    OutputFormat askFormat() const;
};
