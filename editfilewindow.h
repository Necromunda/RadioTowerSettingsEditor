#ifndef EDITFILEWINDOW_H
#define EDITFILEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QJsonArray>
#include <QJsonObject>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QJsonObject json, QString path, QWidget *parent = nullptr);
    ~MainWindow();

    enum AppState
    {
        Init,
        FileOpened,
        LocationSelected,
        LocationUnselected,
        CategorySelected,
        CategoryUnselected,
        ItemSelected,
        ItemUnselected,
        AttachmentCategorySelected,
        AttachmentCategoryUnselected,
        AttachmentSelected,
        AttachmentUnselected
    };

//    void openFile(QString path);
//    bool isFileValid(QString path);
    void refreshView();
    void clearListWidget(QListWidget *listWidget);
    void updateUI();
    void setState(AppState appState);
    void setup(QJsonObject json, QString path);
    void closeEvent(QCloseEvent *event);

signals:
    void CloseWindow();

public slots:
//    void openBtnClicked();
    void saveBtnClicked();

    void addLocationBtnClicked();
    void addCategoryBtnClicked();
    void addItemBtnClicked();
    void addAttachmentCategoryBtnClicked();
    void addAttachmentBtnClicked();
    void addVehicleAttachmentBtnClicked();

    void deleteLocationBtnClicked();
    void deleteCategoryBtnClicked();
    void deleteItemBtnClicked();
    void deleteAttachmentCategoryBtnClicked();
    void deleteAttachmentBtnClicked();
    void deleteVehicleAttachmentBtnClicked();

//    void duplicateLocationBtnClicked();
//    void duplicateCategoryBtnClicked();
//    void duplicateItemBtnClicked();
//    void duplicateAttachmentCategoryBtnClicked();
//    void duplicateAttachmentBtnClicked();
//    void duplicateVehicleAttachmentBtnClicked();

    void radiusSliderValueChanged(int value);
    void heightSliderValueChanged(int value);
    void YOffsetSliderValueChanged(int value);

    void locationLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void categoryLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void itemLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void attachmentCategoryLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void attachmentLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void vehicleAttachmentLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void locationNameLETextChanged(const QString &arg1);
    void locationXCoordinateLETextChanged(const QString &arg1);
    void locationYCoordinateLETextChanged(const QString &arg1);
    void locationZCoordinateLETextChanged(const QString &arg1);
    void locationYOrientationLETextChanged(const QString &arg1);
    void locationPOrientationLETextChanged(const QString &arg1);
    void locationROrientationLETextChanged(const QString &arg1);
    void locationLootcrateClassNameLETextChanged(const QString &arg1);
    void locationLootcrateXCoordinateLETextChanged(const QString &arg1);
    void locationLootcrateYCoordinateLETextChanged(const QString &arg1);
    void locationLootcrateZCoordinateLETextChanged(const QString &arg1);
    void locationLootcrateYOrientationLETextChanged(const QString &arg1);
    void locationLootcratePOrientationLETextChanged(const QString &arg1);
    void locationLootcrateROrientationLETextChanged(const QString &arg1);
    void locationCaptureAreaRadiusSliderValueChanged(int value);
    void locationCaptureAreaHeightSliderValueChanged(int value);
    void locationCaptureAreaYOffsetSliderValueChanged(int value);
    void locationVehicleClassNameLETextChanged(const QString &arg1);
    void locationVehicleXCoordinateLETextChanged(const QString &arg1);
    void locationVehicleYCoordinateLETextChanged(const QString &arg1);
    void locationVehicleZCoordinateLETextChanged(const QString &arg1);
    void locationVehicleYOrientationLETextChanged(const QString &arg1);
    void locationVehiclePOrientationLETextChanged(const QString &arg1);
    void locationVehicleROrientationLETextChanged(const QString &arg1);
    void locationVehicleProbabilityDSBValueChanged(double value);
    void locationZombieCountSBValueChanged(int value);
    void locationLootCountSBValueChanged(int value);
    void categoryNameLETextChanged(const QString &arg1);
    void categoryProbabilityDSBValueChanged(double value);
    void categoryLootLimitSBValueChanged(int value);
    void itemClassNameLETextChanged(const QString &arg1);
    void itemProbabilityDSBValueChanged(double value);
    void itemQuantitySBValueChanged(int value);
    void attachmentCategoryNameLETextChanged(const QString &arg1);
    void attachmentCategoryProbabilityDSBValueChanged(double value);
    void attachmentClassNameLETextChanged(const QString &arg1);
    void attachmentProbabilityDSBValueChanged(double value);   

    void copyLocationBtnClicked();
    void copyVehicleAttachmentBtnClicked();
    void copyCategoryBtnClicked();
    void copyItemBtnClicked();
    void copyAttachmentCategoryBtnClicked();
    void copyAttachmentBtnClicked();

    void pasteLocationBtnClicked();
    void pasteVehicleAttachmentBtnClicked();
    void pasteCategoryBtnClicked();
    void pasteItemBtnClicked();
    void pasteAttachmentCategoryBtnClicked();
    void pasteAttachmentBtnClicked();
private:
    Ui::MainWindow *ui;

//    QStringList filenames = {"RTLocations"};
    QJsonObject jsonRootObj;
    QString filepath;
    AppState state;
    QJsonArray copiedLocations, copiedCategories, copiedItems, copiedAttachmentCategories, copiedAttachments, copiedVehicleAttachments;
    int selectedLocationIndex, selectedCategoryIndex, selectedItemIndex, selectedAttachmentCategoryIndex, selectedAttachmentIndex;
    double totalCategoriesProbability, totalItemsProbability, totalAttachmentCategoriesProbability, totalAttachmentsProbability;
};
#endif // EDITFILEWINDOW_H
