#include <QApplication>
#include <QKeySequence>
#include <QMainWindow>
#include <QDesktopServices>
#include "qtermwidget.h"
#include <QDesktopServices>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QMainWindow *mainWindow = new QMainWindow();

  QTermWidget *console = new QTermWidget();

  QFont font = QApplication::font();
  font.setFamily("Monospace");
  font.setPointSize(15);

  console->setTerminalFont(font);

  console->setTerminalFont(font);
  console->setColorScheme("Solarized");

  console->setTerminalOpacity(0.9);

  mainWindow->resize(600, 400);

   // Here we'll allow copying text
  QObject::connect(console, &QTermWidget::termKeyPressed, mainWindow,
                   [=](const QKeyEvent *key) -> void {
                     if (key->matches(QKeySequence::Copy)) {
                       console->copyClipboard();
					   // Now we can paste too
                     } else if (key->matches(QKeySequence::Paste)) {
                       console->pasteClipboard();
                     }
                   });

  QObject::connect(console, SIGNAL(finished()), mainWindow, SLOT(close()));

  mainWindow->setCentralWidget(console);

  mainWindow->show();
  return app.exec();
}

