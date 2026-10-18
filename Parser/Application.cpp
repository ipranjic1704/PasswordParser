#include "Application.h"
#include "FileReader.h"
#include "CsvParser.h"
#include "ExporterFactory.h"
#include "Exceptions.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {
    const std::string kDefaultInput = "Comet Passwords.csv";
}

std::string Application::askInputPath() const {
    std::cout << "Putanja do CSV datoteke [" << kDefaultInput << "]: ";
    std::string line;
    std::getline(std::cin, line);
    if (line.empty()) return kDefaultInput; // Enter -> zadano
    return line;
}

OutputFormat Application::askFormat() const {
    // Petlja dok korisnik ne da valjan izbor -- otporno na krivi unos.
    while (true) {
        std::cout << "\nOdaberi format izlaza:\n"
                  << "  1) HTML  (otvara se u Wordu i Excelu)\n"
                  << "  2) CSV   (otvara se u Excelu)\n"
                  << "  3) TXT   (obicni tekst)\n"
                  << "Izbor: ";

        std::string line;
        if (!std::getline(std::cin, line)) {
            // Kraj ulaza (npr. preusmjeren stdin) -> razuman zadani format.
            std::cout << "\n(Nema vise unosa -- koristim HTML.)\n";
            return OutputFormat::Html;
        }

        if (line == "1") return OutputFormat::Html;
        if (line == "2") return OutputFormat::Csv;
        if (line == "3") return OutputFormat::Txt;

        std::cout << "Nepoznat izbor '" << line << "'. Pokusaj ponovno.\n";
    }
}

int Application::run() {
    std::cout << "=== Parser lozinki (lokalno, bez mreze) ===\n\n";

    try {
        const std::string inputPath = askInputPath();

        FileReader reader;
        const std::string content = reader.readAll(inputPath);

        CsvParser parser;
        std::vector<PasswordRecord> records = parser.parse(content);

        // Zadrzi samo valjane zapise (pravilo definira PasswordRecord::isValid).
        std::vector<PasswordRecord> valid;
        valid.reserve(records.size());
        for (auto& r : records) {
            if (r.isValid()) valid.push_back(std::move(r));
        }

        if (valid.empty()) {
            std::cout << "Datoteka je procitana, ali nema valjanih zapisa.\n";
            return 0; // nije greska -- samo nema sto izvesti
        }
        std::cout << "Ucitano valjanih zapisa: " << valid.size() << "\n";

        const OutputFormat format = askFormat();

        ExporterFactory factory;
        const auto exporter = factory.create(format);
        const std::string outPath = exporter->defaultFileName();

        exporter->exportTo(valid, outPath);
        std::cout << "\nSpremljeno: " << outPath << "\n";
        return 0;
    }
    catch (const AppException& e) {
        // Ocekivane greske (datoteka, izvoz) -- jasna poruka, bez pada.
        std::cerr << "\nGreska: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e) {
        // Bilo koja druga standardna greska.
        std::cerr << "\nNeocekivana greska: " << e.what() << "\n";
        return 2;
    }
    catch (...) {
        // Krajnja mreza -- apsolutno sve ostalo.
        std::cerr << "\nNepoznata greska. Aplikacija zavrsava sigurno.\n";
        return 3;
    }
}
