#ifndef SELECTFILEWINDOW_H
#define SELECTFILEWINDOW_H

#include "editfilewindow.h"

#include <QMainWindow>

namespace Ui {
class SelectFileWindow;
}

class SelectFileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectFileWindow(QWidget *parent = nullptr);
    ~SelectFileWindow();

    bool isFileValid(QString path);
//    void openFile(QString path);

public slots:
    void editorClosed();
    void createFile();
    void browseFilesBtnClicked();
    void editFileBtnClicked();

private:
    Ui::SelectFileWindow *ui;
    MainWindow *editor;
    QStringList filenames = {"RTLocations"};
};

#endif // SELECTFILEWINDOW_H
