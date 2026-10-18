#include "Application.h"

// Ulazna tocka: jedina odgovornost je stvoriti i pokrenuti aplikaciju.
// Sva logika zivi u klasama (SRP), a Application jamci da nista ne pukne.
int main() {
    Application app;
    return app.run();
}
