#pragma once
#include "IExporter.h"
#include "OutputFormat.h"
#include <memory>

// Odgovornost: za dani format stvoriti odgovarajuci izvoznik.
// Application tako ne mora znati konkretne klase (ovisi o IExporter-u).
class ExporterFactory {
public:
    // Vraca izvoznik za trazeni format (vlasnistvo preuzima pozivatelj).
    std::unique_ptr<IExporter> create(OutputFormat format) const;
};
