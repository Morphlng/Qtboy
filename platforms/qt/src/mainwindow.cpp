#include <QtWidgets>
#include "mainwindow.h"
#include "disassemblerwindow.h"
#include "debuggerwindow.h"
#include "vram_window.h"
#include "qt_speaker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow {parent},
      renderer_ {new Qt_renderer(160, 144)},
      speaker_ {new Qt_speaker},
      display {new QLabel}
{

    system.set_renderer(renderer_);
    system.set_speaker(speaker_);
    createActions();
    display->setScaledContents(true);
    setCentralWidget(display);
    connect(renderer_, SIGNAL(present_screen()), this, SLOT(update_display()));
}


void MainWindow::loadRom(const QString &fileName)
{
    system.reset();
    system.load_cartridge(fileName.toStdString());
    system.run_concurrently();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_S:
            system.press(gameboy::Joypad::Input::B);
            break;
        case Qt::Key_A:
            system.press(gameboy::Joypad::Input::A);
            break;
        case Qt::Key_Up:
            system.press(gameboy::Joypad::Input::Up);
            break;
        case Qt::Key_Down:
            system.press(gameboy::Joypad::Input::Down);
            break;
        case Qt::Key_Left:
            system.press(gameboy::Joypad::Input::Left);
            break;
        case Qt::Key_Right:
            system.press(gameboy::Joypad::Input::Right);
            break;
        case Qt::Key_Shift:
            system.press(gameboy::Joypad::Input::Select);
            break;
        case Qt::Key_Return:
            system.press(gameboy::Joypad::Input::Start);
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_S:
            system.release(gameboy::Joypad::Input::B);
            break;
        case Qt::Key_A:
            system.release(gameboy::Joypad::Input::A);
            break;
        case Qt::Key_Up:
            system.release(gameboy::Joypad::Input::Up);
            break;
        case Qt::Key_Down:
            system.release(gameboy::Joypad::Input::Down);
            break;
        case Qt::Key_Left:
            system.release(gameboy::Joypad::Input::Left);
            break;
        case Qt::Key_Right:
            system.release(gameboy::Joypad::Input::Right);
            break;
        case Qt::Key_Shift:
            system.release(gameboy::Joypad::Input::Select);
            break;
        case Qt::Key_Return:
            system.release(gameboy::Joypad::Input::Start);
            break;
    }
}

void MainWindow::openRom()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadRom(fileName);
}

void MainWindow::showDisassembler()
{
    auto disassembler = new DisassemblerWindow(this, &system);
    disassembler->show();
}

void MainWindow::showDebugger()
{
    auto debugger = new Debugger_window(this, &system);
    debugger->show();
}

void MainWindow::showVramViewer()
{
    auto vram_viewer = new Vram_window(&system);
    vram_viewer->show();
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About QtBoy"),
                       tr("A Gameboy emulator made using Qt."));
}

void MainWindow::update_display()
{
    QImage img {renderer_->image()};
    display->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAct = fileMenu->addAction(tr("&Open"), this, &MainWindow::openRom);
    openAct->setShortcuts(QKeySequence::Open);

    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
    QAction *disassembleAct = toolsMenu->addAction(tr("Disassemble"), this, &MainWindow::showDisassembler);
    QAction *debuggerAct = toolsMenu->addAction(tr("Debugger"), this, &MainWindow::showDebugger);
    QAction *vramViewerAct = toolsMenu->addAction(tr("VRAM Viewer"), this, &MainWindow::showVramViewer);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
}
