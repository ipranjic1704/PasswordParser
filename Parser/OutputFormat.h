#pragma once

// Podrzani izlazni formati. Dodavanje novog clana ovdje + nove IExporter
// klase + grane u ExporterFactory = cijela nova mogucnost.
enum class OutputFormat {
    Html,   // otvara se u Wordu i Excelu
    Csv,    // otvara se u Excelu
    Txt     // obicni tekst
};
