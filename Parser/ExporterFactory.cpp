#include "ExporterFactory.h"
#include "HtmlExporter.h"
#include "CsvExporter.h"
#include "TxtExporter.h"

std::unique_ptr<IExporter> ExporterFactory::create(OutputFormat format) const {
    switch (format) {
        case OutputFormat::Html: return std::make_unique<HtmlExporter>();
        case OutputFormat::Csv:  return std::make_unique<CsvExporter>();
        case OutputFormat::Txt:  return std::make_unique<TxtExporter>();
    }
    // Obrambeni zadani slucaj -- ako se enum prosiri a grana zaboravi.
    return std::make_unique<TxtExporter>();
}
