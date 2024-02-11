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

    void initSettings();
    QJsonObject loadSettings();
    void saveToSettings(QString key, QJsonValue str, bool showPopup = false);

public slots:
    void editorClosed();
    void createFile();
    void browseFilesBtnClicked();
    void editFileBtnClicked();
    void savePathBtnClicked();

private:
    Ui::SelectFileWindow *ui;
    MainWindow *editor;
    QStringList filenames = {"RTLocations"};
    QString settingsFile = "./settings.json";
    QString settingsFilePath = "C:/Program Files/RadioTowerSettingsEditor/";
};

#endif // SELECTFILEWINDOW_H
