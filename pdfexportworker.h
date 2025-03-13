#ifndef PDFEXPORTWORKER_H
#define PDFEXPORTWORKER_H

#include <QObject>
#include <QString>
#include <QPrinter>
#include <QTextDocument>

class PdfExportWorker : public QObject
{
    Q_OBJECT
public:
    explicit PdfExportWorker(const QString &path, const QString &html, bool compressionOn, QObject *parent = nullptr)
        : QObject(parent), m_path(path), m_html(html), m_compressionOn(compressionOn) {}

public slots:
    void process() {
        // Create printer for PDF export.
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(m_path);

        // Simulate compression by lowering resolution if compression is ON.
        if (m_compressionOn)
            printer.setResolution(72);
        else
            printer.setResolution(300);

        QTextDocument doc;
        doc.setHtml(m_html);
        doc.print(&printer);

        emit finished();
    }

signals:
    void finished();
    void error(const QString &errMsg);

private:
    QString m_path;
    QString m_html;
    bool m_compressionOn;
};

#endif // PDFEXPORTWORKER_H
