#include "selectfilewindow.h"
#include "ui_selectfilewindow.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

SelectFileWindow::SelectFileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectFileWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->browseFilesBtn,    &QPushButton::clicked, this, &SelectFileWindow::browseFilesBtnClicked);
    QObject::connect(ui->editFileBtn,       &QPushButton::clicked, this, &SelectFileWindow::editFileBtnClicked);
    QObject::connect(ui->createNewFileBtn,  &QPushButton::clicked, this, &SelectFileWindow::createFile);
    QObject::connect(ui->savePathBtn,       &QPushButton::clicked, this, &SelectFileWindow::savePathBtnClicked);

    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_DirIcon);
    ui->browseFilesBtn->setIcon(icon);

    initSettings();

    QJsonObject settings = loadSettings();
    QJsonValue loadedPath = settings["RTLocationsPath"];
    if (loadedPath.isNull())
    {
        saveToSettings("RTLocationsPath", "");
    }
    else
    {
        ui->filepathLE->setText(loadedPath.toString());
    }
}

SelectFileWindow::~SelectFileWindow()
{
    delete ui;
    delete editor;
}

void SelectFileWindow::editorClosed()
{
    qDebug() << "Editor closed";
    this->show();
}

bool SelectFileWindow::isFileValid(QString path)
{
    for (int i = 0; i < filenames.size(); i++)
    {
        if (path.contains(filenames[i], Qt::CaseInsensitive))
        {
            return true;
        }
    }
    return false;
}

void SelectFileWindow::createFile()
{
    QJsonArray eventLocations;
    QJsonObject root, eventLocation, loot;
    QJsonArray defaultArray = {0,0,0};

    eventLocation.insert("captureAreaRadius", QJsonValue::fromVariant(0));
    eventLocation.insert("captureAreaHeight", QJsonValue::fromVariant(0));
    eventLocation.insert("captureAreaYAxisOffset", QJsonValue::fromVariant(0));
    eventLocation.insert("locationTitle", QJsonValue::fromVariant(""));
    eventLocation.insert("lootcrateClassName", QJsonValue::fromVariant(""));
    eventLocation.insert("zombieCount", QJsonValue::fromVariant(0));
    eventLocation.insert("locationCoordinatesXYZ", QJsonValue::fromVariant(defaultArray));
    eventLocation.insert("locationOrientationYPR", QJsonValue::fromVariant(defaultArray));
    eventLocation.insert("lootcrateCoordinatesXYZ", QJsonValue::fromVariant(defaultArray));
    eventLocation.insert("lootcrateOrientationYPR", QJsonValue::fromVariant(defaultArray));
    eventLocation.insert("vehicleCoordinatesXYZ", QJsonValue::fromVariant(defaultArray));
    eventLocation.insert("vehicleOrientationYPR", QJsonValue::fromVariant(defaultArray));
    eventLocation.insert("vehicleProbability", QJsonValue::fromVariant(0));
    eventLocation.insert("vehicleClassName", QJsonValue::fromVariant(""));
    eventLocation.insert("vehicleAttachments", QJsonValue::fromVariant(QJsonArray()));
    loot.insert("lootCount", QJsonValue::fromVariant(0));
    loot.insert("lootCategories", QJsonValue::fromVariant(QJsonArray()));
    eventLocation.insert("loot", QJsonValue::fromVariant(loot));
    eventLocations.append(eventLocation);
    root.insert("eventLocations", QJsonValue::fromVariant(eventLocations));

    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), "C:/", tr("JSON Files (*.json);;All Files (*)"));

    if (!filePath.isEmpty())
    {
        // Attempt to open the file for writing
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // Convert the JSON data to a QByteArray
            QJsonDocument doc(eventLocations);
            QByteArray data = doc.toJson();

            // Write the JSON data to the file
            file.write(data);

            // Close the file
            file.close();

            QMessageBox::information(this, tr("Save Successful"), tr("File saved successfully."));

            ui->filepathLE->setText(filePath);
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not save the file."));
        }
    }
}

void SelectFileWindow::browseFilesBtnClicked()
{
//    qDebug() << "Select file";

    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/", tr("Files (*.json)"));

    if (path.isEmpty())
        return;

    bool isValid = isFileValid(path);

    if (!isValid)
    {
        QMessageBox::warning(this, tr("File not valid"), tr("This tool can only be used to edit RTLocations.json"));
        return;
    }

    ui->filepathLE->setText(path);
}

void SelectFileWindow::editFileBtnClicked()
{
    QString path = ui->filepathLE->text();
    QString val;
    QFile file(path);

    if (path.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), tr("File not selected"));
        return;
    }

    if (!file.exists())
    {
        QMessageBox::warning(this, tr("Error"), tr("File not found"));
        return;
    }

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonRootObj = doc.object();
    editor = new MainWindow(jsonRootObj, path, this);
    editor->show();
    this->hide();
    QObject::connect(editor, &MainWindow::CloseWindow, this, &SelectFileWindow::editorClosed);
}

void SelectFileWindow::savePathBtnClicked()
{
    QString path = ui->filepathLE->text();

    if (path.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), tr("Path is empty"));
        return;
    }

    saveToSettings("RTLocationsPath", path, true);
}

void SelectFileWindow::initSettings()
{
    QDir dir = QDir(settingsFilePath);
    if (!dir.exists())
    {
        dir.mkpath(settingsFilePath);
    }
}

QJsonObject SelectFileWindow::loadSettings()
{
    QString val;
    QFile file(settingsFilePath + settingsFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        val = file.readAll();
        file.close();
    }
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonRootObj = doc.object();
    return jsonRootObj;
}

void SelectFileWindow::saveToSettings(QString key, QJsonValue value, bool showPopup)
{
    QJsonObject root;
    root = loadSettings();
    root[key] = value;

    QFile file(settingsFilePath + settingsFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonDocument doc(root);
        QByteArray data = doc.toJson();
        file.write(data);
        file.close();

        if (showPopup)
        {
            QMessageBox::information(this, tr("Save Successful"), tr("Path saved successfully."));
        }
    }
    else
    {
        if (showPopup)
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not save the path."));
        }
    }
}
