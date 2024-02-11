#include "editfilewindow.h"
#include "ui_editfilewindow.h"

#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

MainWindow::MainWindow(QJsonObject json, QString path, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->saveBtn,                             &QPushButton::clicked, this, &MainWindow::saveBtnClicked);

    QObject::connect(ui->addLocationBtn,                      &QPushButton::clicked, this, &MainWindow::addLocationBtnClicked);
    QObject::connect(ui->addCategoryBtn,                      &QPushButton::clicked, this, &MainWindow::addCategoryBtnClicked);
    QObject::connect(ui->addItemBtn,                          &QPushButton::clicked, this, &MainWindow::addItemBtnClicked);
    QObject::connect(ui->addAttachmentCategoryBtn,            &QPushButton::clicked, this, &MainWindow::addAttachmentCategoryBtnClicked);
    QObject::connect(ui->addAttachmentBtn,                    &QPushButton::clicked, this, &MainWindow::addAttachmentBtnClicked);
    QObject::connect(ui->addVehicleAttachmentBtn,             &QPushButton::clicked, this, &MainWindow::addVehicleAttachmentBtnClicked);

    QObject::connect(ui->deleteLocationBtn,                   &QPushButton::clicked, this, &MainWindow::deleteLocationBtnClicked);
    QObject::connect(ui->deleteCategoryBtn,                   &QPushButton::clicked, this, &MainWindow::deleteCategoryBtnClicked);
    QObject::connect(ui->deleteItemBtn,                       &QPushButton::clicked, this, &MainWindow::deleteItemBtnClicked);
    QObject::connect(ui->deleteAttachmentCategoryBtn,         &QPushButton::clicked, this, &MainWindow::deleteAttachmentCategoryBtnClicked);
    QObject::connect(ui->deleteAttachmentBtn,                 &QPushButton::clicked, this, &MainWindow::deleteAttachmentBtnClicked);
    QObject::connect(ui->deleteVehicleAttachmentBtn,          &QPushButton::clicked, this, &MainWindow::deleteVehicleAttachmentBtnClicked);

    QObject::connect(ui->copyLocationBtn,                     &QPushButton::clicked, this, &MainWindow::copyLocationBtnClicked);
    QObject::connect(ui->copyVehicleAttachmentBtn,            &QPushButton::clicked, this, &MainWindow::copyVehicleAttachmentBtnClicked);
    QObject::connect(ui->copyCategoryBtn,                     &QPushButton::clicked, this, &MainWindow::copyCategoryBtnClicked);
    QObject::connect(ui->copyItemBtn,                         &QPushButton::clicked, this, &MainWindow::copyItemBtnClicked);
    QObject::connect(ui->copyAttachmentCategoryBtn,           &QPushButton::clicked, this, &MainWindow::copyAttachmentCategoryBtnClicked);
    QObject::connect(ui->copyAttachmentBtn,                   &QPushButton::clicked, this, &MainWindow::copyAttachmentBtnClicked);

    QObject::connect(ui->pasteLocationBtn,                    &QPushButton::clicked, this, &MainWindow::pasteLocationBtnClicked);
    QObject::connect(ui->pasteVehicleAttachmentBtn,           &QPushButton::clicked, this, &MainWindow::pasteVehicleAttachmentBtnClicked);
    QObject::connect(ui->pasteCategoryBtn,                    &QPushButton::clicked, this, &MainWindow::pasteCategoryBtnClicked);
    QObject::connect(ui->pasteItemBtn,                        &QPushButton::clicked, this, &MainWindow::pasteItemBtnClicked);
    QObject::connect(ui->pasteAttachmentCategoryBtn,          &QPushButton::clicked, this, &MainWindow::pasteAttachmentCategoryBtnClicked);
    QObject::connect(ui->pasteAttachmentBtn,                  &QPushButton::clicked, this, &MainWindow::pasteAttachmentBtnClicked);

    QObject::connect(ui->locationCaptureAreaRadiusSlider,     &QSlider::valueChanged, this, &MainWindow::radiusSliderValueChanged);
    QObject::connect(ui->locationCaptureAreaHeightSlider,     &QSlider::valueChanged, this, &MainWindow::heightSliderValueChanged);
    QObject::connect(ui->locationCaptureAreaYOffsetSlider,    &QSlider::valueChanged, this, &MainWindow::YOffsetSliderValueChanged);

    QObject::connect(ui->locationsLW,                         &QListWidget::currentItemChanged, this, &MainWindow::locationLWItemChanged);
    QObject::connect(ui->categoriesLW,                        &QListWidget::currentItemChanged, this, &MainWindow::categoryLWItemChanged);
    QObject::connect(ui->itemsLW,                             &QListWidget::currentItemChanged, this, &MainWindow::itemLWItemChanged);
    QObject::connect(ui->attachmentCategoriesLW,              &QListWidget::currentItemChanged, this, &MainWindow::attachmentCategoryLWItemChanged);
    QObject::connect(ui->attachmentsLW,                       &QListWidget::currentItemChanged, this, &MainWindow::attachmentLWItemChanged);
    QObject::connect(ui->vehicleAttachmentsLW,                &QListWidget::currentItemChanged, this, &MainWindow::vehicleAttachmentLWItemChanged);

    QObject::connect(ui->locationNameLE,                      &QLineEdit::textChanged, this, &MainWindow::locationNameLETextChanged);
    QObject::connect(ui->locationLootcrateLE,                 &QLineEdit::textChanged, this, &MainWindow::locationLootcrateClassNameLETextChanged);
    QObject::connect(ui->locationVehicleNameLE,               &QLineEdit::textChanged, this, &MainWindow::locationVehicleClassNameLETextChanged);
    QObject::connect(ui->categoryNameLE,                      &QLineEdit::textChanged, this, &MainWindow::categoryNameLETextChanged);
    QObject::connect(ui->itemNameLE,                          &QLineEdit::textChanged, this, &MainWindow::itemClassNameLETextChanged);
    QObject::connect(ui->attachmentCategoryNameLE,            &QLineEdit::textChanged, this, &MainWindow::attachmentCategoryNameLETextChanged);
    QObject::connect(ui->attachmentNameLE,                    &QLineEdit::textChanged, this, &MainWindow::attachmentClassNameLETextChanged);

    QObject::connect(ui->locationXCoordinateLE,               &QLineEdit::textChanged, this, &MainWindow::locationXCoordinateLETextChanged);
    QObject::connect(ui->locationLootcrateXCoordinateLE,      &QLineEdit::textChanged, this, &MainWindow::locationLootcrateXCoordinateLETextChanged);
    QObject::connect(ui->locationVehicleXCoordinateLE,        &QLineEdit::textChanged, this, &MainWindow::locationVehicleXCoordinateLETextChanged);

    QObject::connect(ui->locationYCoordinateLE,               &QLineEdit::textChanged, this, &MainWindow::locationYCoordinateLETextChanged);
    QObject::connect(ui->locationLootcrateYCoordinateLE,      &QLineEdit::textChanged, this, &MainWindow::locationLootcrateYCoordinateLETextChanged);
    QObject::connect(ui->locationVehicleYCoordinateLE,        &QLineEdit::textChanged, this, &MainWindow::locationVehicleYCoordinateLETextChanged);

    QObject::connect(ui->locationZCoordinateLE,               &QLineEdit::textChanged, this, &MainWindow::locationZCoordinateLETextChanged);
    QObject::connect(ui->locationLootcrateZCoordinateLE,      &QLineEdit::textChanged, this, &MainWindow::locationLootcrateZCoordinateLETextChanged);
    QObject::connect(ui->locationVehicleZCoordinateLE,        &QLineEdit::textChanged, this, &MainWindow::locationVehicleZCoordinateLETextChanged);

    QObject::connect(ui->locationYOrientationLE,              &QLineEdit::textChanged, this, &MainWindow::locationYOrientationLETextChanged);
    QObject::connect(ui->locationLootcrateYOrientationLE,     &QLineEdit::textChanged, this, &MainWindow::locationLootcrateYOrientationLETextChanged);
    QObject::connect(ui->locationVehicleYOrientationLE,       &QLineEdit::textChanged, this, &MainWindow::locationVehicleYOrientationLETextChanged);

    QObject::connect(ui->locationPOrientationLE,              &QLineEdit::textChanged, this, &MainWindow::locationPOrientationLETextChanged);
    QObject::connect(ui->locationLootcratePOrientationLE,     &QLineEdit::textChanged, this, &MainWindow::locationLootcratePOrientationLETextChanged);
    QObject::connect(ui->locationVehiclePOrientationLE,       &QLineEdit::textChanged, this, &MainWindow::locationVehiclePOrientationLETextChanged);

    QObject::connect(ui->locationROrientationLE,              &QLineEdit::textChanged, this, &MainWindow::locationROrientationLETextChanged);
    QObject::connect(ui->locationVehicleROrientationLE,       &QLineEdit::textChanged, this, &MainWindow::locationVehicleROrientationLETextChanged);
    QObject::connect(ui->locationLootcrateROrientationLE,     &QLineEdit::textChanged, this, &MainWindow::locationLootcrateROrientationLETextChanged);

    QObject::connect(ui->locationCaptureAreaRadiusSlider,     &QSlider::valueChanged, this, &MainWindow::locationCaptureAreaRadiusSliderValueChanged);
    QObject::connect(ui->locationCaptureAreaHeightSlider,     &QSlider::valueChanged, this, &MainWindow::locationCaptureAreaHeightSliderValueChanged);
    QObject::connect(ui->locationCaptureAreaYOffsetSlider,    &QSlider::valueChanged, this, &MainWindow::locationCaptureAreaYOffsetSliderValueChanged);

    QObject::connect(ui->locationZombieCountSB,               &QSpinBox::valueChanged, this, &MainWindow::locationZombieCountSBValueChanged);
    QObject::connect(ui->locationLootCountSB,                 &QSpinBox::valueChanged, this, &MainWindow::locationLootCountSBValueChanged);
    QObject::connect(ui->categoryLootLimitSB,                 &QSpinBox::valueChanged, this, &MainWindow::categoryLootLimitSBValueChanged);
    QObject::connect(ui->itemQuantitySB,                      &QSpinBox::valueChanged, this, &MainWindow::itemQuantitySBValueChanged);

    QObject::connect(ui->locationVehicleProbabilityDSB,       &QDoubleSpinBox::valueChanged, this, &MainWindow::locationVehicleProbabilityDSBValueChanged);
    QObject::connect(ui->categoryProbabilityDSB,              &QDoubleSpinBox::valueChanged, this, &MainWindow::categoryProbabilityDSBValueChanged);
    QObject::connect(ui->itemProbabilityDSB,                  &QDoubleSpinBox::valueChanged, this, &MainWindow::itemProbabilityDSBValueChanged);
    QObject::connect(ui->attachmentCategoryProbabilityDSB,    &QDoubleSpinBox::valueChanged, this, &MainWindow::attachmentCategoryProbabilityDSBValueChanged);
    QObject::connect(ui->attachmentProbabilityDSB,            &QDoubleSpinBox::valueChanged, this, &MainWindow::attachmentProbabilityDSBValueChanged);

    QObject::connect(ui->categoryLootRandomizeQuantityCheckBox, &QCheckBox::clicked, this, &MainWindow::categoryLootRandomizeQuantityCheckBoxClicked);

    setState(MainWindow::Init);
    setup(json, path);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit CloseWindow();
    QMainWindow::closeEvent(event);
}

void MainWindow::setup(QJsonObject json, QString path)
{
    filepath = path;
    jsonRootObj = json;

    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    for (int i = 0; i < locations.size(); i++)
    {
        QJsonObject location = locations[i].toObject();
        QString title = location["locationTitle"].toString();
        ui->locationsLW->addItem(title);
    }

    // Hide these for now because we dont need them
    ui->attachmentCategoriesTotalProbabilityLabel->hide();
    ui->attachmentCategoriesTotalProbabilityValueLabel->hide();

    setState(MainWindow::FileOpened);
}

void MainWindow::setState(AppState appState)
{
    state = appState;
    updateUI();
}

void MainWindow::updateUI()
{
    switch (state)
    {
        case MainWindow::Init:
            ui->mainGB->hide();
            ui->saveBtn->hide();
            break;
        case MainWindow::FileOpened:
            ui->mainGB->show();
            ui->saveBtn->show();
            ui->categoriesGB->hide();
            ui->itemsGB->hide();
            ui->locationSettingsGB->hide();
            ui->attachmentCategoriesGB->hide();
            ui->attachmentsGB->hide();
            ui->lootSettingsGB->hide();
            break;
        case MainWindow::LocationSelected:
            ui->categoriesGB->show();
            ui->itemsGB->hide();
            ui->attachmentCategoriesGB->hide();
            ui->attachmentsGB->hide();

            ui->locationSettingsGB->show();
            ui->lootSettingsGB->hide();
            break;
        case MainWindow::LocationUnselected:
            ui->categoriesGB->hide();
            ui->itemsGB->hide();
            ui->attachmentCategoriesGB->hide();
            ui->attachmentsGB->hide();

            ui->locationSettingsGB->hide();
            ui->lootSettingsGB->hide();
            break;
        case MainWindow::CategorySelected:
            ui->itemsGB->show();
            ui->attachmentCategoriesGB->hide();
            ui->attachmentsGB->hide();

            ui->categorySettingsGB->show();
            ui->lootSettingsGB->show();
            ui->itemSettingsGB->hide();
            ui->attachmentCategorySettingsGB->hide();
            ui->attachmentSettingsGB->hide();
            break;
        case MainWindow::CategoryUnselected:
            ui->itemsGB->hide();
            ui->attachmentCategoriesGB->hide();
            ui->attachmentsGB->hide();

            ui->lootSettingsGB->hide();
            break;
        case MainWindow::ItemSelected:
            ui->attachmentCategoriesGB->show();
            ui->attachmentsGB->hide();

            ui->itemSettingsGB->show();
            ui->attachmentCategorySettingsGB->hide();
            ui->attachmentSettingsGB->hide();
            break;
        case MainWindow::ItemUnselected:
            ui->attachmentCategoriesGB->hide();
            ui->attachmentsGB->hide();

            ui->itemSettingsGB->hide();
            ui->attachmentCategorySettingsGB->hide();
            ui->attachmentSettingsGB->hide();
            break;
        case MainWindow::AttachmentCategorySelected:
            ui->attachmentsGB->show();

            ui->attachmentCategorySettingsGB->show();
            ui->attachmentSettingsGB->hide();
            break;
        case MainWindow::AttachmentCategoryUnselected:
            ui->attachmentsGB->hide();

            ui->attachmentCategorySettingsGB->hide();
            ui->attachmentSettingsGB->hide();
            break;
        case MainWindow::AttachmentSelected:
            ui->attachmentSettingsGB->show();
            break;
        case MainWindow::AttachmentUnselected:
            ui->attachmentSettingsGB->hide();
            break;
    }
}

void MainWindow::saveBtnClicked()
{
    QFile file;
    file.setFileName(filepath);
    if (!file.exists())
    {
        QMessageBox::warning(this, tr("Error"), tr("File not found, check filepath"));
        return;
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonDocument jsonDoc(jsonRootObj);
        QByteArray jsonData = jsonDoc.toJson();
        file.write(jsonData);
        file.close();

        QMessageBox::information(this, tr("Save Successful"), tr("File saved successfully."));
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not save the file."));
    }
}

void MainWindow::addLocationBtnClicked()
{
    QString text = ui->locationsLE->text();
    if (text.isEmpty()) return;

    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location, loot;
    QJsonArray defaultArray = {0,0,0};

    location.insert("captureAreaRadius", QJsonValue::fromVariant(0));
    location.insert("captureAreaHeight", QJsonValue::fromVariant(0));
    location.insert("captureAreaYAxisOffset", QJsonValue::fromVariant(0));
    location.insert("locationTitle", QJsonValue::fromVariant(text));
    location.insert("lootcrateClassName", QJsonValue::fromVariant(""));
    location.insert("zombieCount", QJsonValue::fromVariant(0));
    location.insert("locationCoordinatesXYZ", QJsonValue::fromVariant(defaultArray));
    location.insert("locationOrientationYPR", QJsonValue::fromVariant(defaultArray));
    location.insert("lootcrateCoordinatesXYZ", QJsonValue::fromVariant(defaultArray));
    location.insert("lootcrateOrientationYPR", QJsonValue::fromVariant(defaultArray));
    location.insert("vehicleCoordinatesXYZ", QJsonValue::fromVariant(defaultArray));
    location.insert("vehicleOrientationYPR", QJsonValue::fromVariant(defaultArray));
    location.insert("vehicleProbability", QJsonValue::fromVariant(0));
    location.insert("vehicleClassName", QJsonValue::fromVariant(""));
    location.insert("vehicleAttachments", QJsonValue::fromVariant(QJsonArray()));
    loot.insert("lootCount", QJsonValue::fromVariant(0));
    loot.insert("lootCategories", QJsonValue::fromVariant(QJsonArray()));
    location.insert("loot", QJsonValue::fromVariant(loot));
    locations.append(location);
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::deleteLocationBtnClicked()
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QList<QListWidgetItem *> selectedLocations = ui->locationsLW->selectedItems();

    QList<int> deleteIndexes = {};
    for (int i = 0; i < selectedLocations.size(); i++)
    {
        deleteIndexes.append(ui->locationsLW->indexFromItem(selectedLocations[i]).row());
    }
    std::sort(deleteIndexes.begin(), deleteIndexes.end());
    std::reverse(deleteIndexes.begin(), deleteIndexes.end());
    for (int i = 0; i < deleteIndexes.size(); i++)
    {
        locations.removeAt(deleteIndexes[i]);
    }
    jsonRootObj["eventLocations"] = locations;

    ui->locationsLE->clear();
    this->refreshView();
    setState(MainWindow::LocationUnselected);
}

void MainWindow::copyLocationBtnClicked()
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QList<QListWidgetItem *> selectedLocations = ui->locationsLW->selectedItems();

    copiedLocations = {};
    for (int i = 0; i < selectedLocations.size(); i++)
    {
        int index = ui->locationsLW->indexFromItem(selectedLocations[i]).row();

        copiedLocations.append(locations[index]);
    }
}

void MainWindow::pasteLocationBtnClicked()
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();

    foreach (auto location, copiedLocations) {
        locations.append(location);
    }

    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::refreshView()
{
    clearListWidget(ui->locationsLW);
    clearListWidget(ui->categoriesLW);
    clearListWidget(ui->itemsLW);
    clearListWidget(ui->attachmentCategoriesLW);
    clearListWidget(ui->attachmentsLW);
    clearListWidget(ui->vehicleAttachmentsLW);

    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    for (int i = 0; i < locations.size(); i++)
    {
        QJsonObject location = locations[i].toObject();
        QString title = location["locationTitle"].toString();
        ui->locationsLW->addItem(title);
    }

    QJsonArray vehicleAttachments = locations[selectedLocationIndex].toObject()["vehicleAttachments"].toArray();
    for (int i = 0; i < vehicleAttachments.size(); i++)
    {
        QString vehicleAttachment = vehicleAttachments[i].toString();
        ui->vehicleAttachmentsLW->addItem(vehicleAttachment);
    }

    totalCategoriesProbability = 0.0;
    QJsonArray categories = locations[selectedLocationIndex].toObject()["loot"].toObject()["lootCategories"].toArray();
    for (int i = 0; i < categories.size(); i++)
    {
        QJsonObject category = categories[i].toObject();
        QString title = category["lootCategoryTitle"].toString();
        totalCategoriesProbability += category["probability"].toDouble();
        ui->categoriesLW->addItem(title);
    }
    ui->categoriesTotalProbabilityValueLabel->setText(QString("%1").arg(totalCategoriesProbability, 0, 'f', 5));

    totalItemsProbability = 0.0;
    QJsonArray items = categories[selectedCategoryIndex].toObject()["items"].toArray();
    for (int i = 0; i < items.size(); i++)
    {
        QJsonObject item = items[i].toObject();
        QString title = item["lootItemClassName"].toString();
        totalItemsProbability += item["probability"].toDouble();
        ui->itemsLW->addItem(title);
    }
    ui->itemsTotalProbabilityValueLabel->setText(QString("%1").arg(totalItemsProbability, 0, 'f', 5));

    totalAttachmentCategoriesProbability = 0.0;
    QJsonArray attachmentCategories = items[selectedItemIndex].toObject()["attachmentCategories"].toArray();
    for (int i = 0; i < attachmentCategories.size(); i++)
    {
        QJsonObject attachmentCategory = attachmentCategories[i].toObject();
        QString title = attachmentCategory["attachmentCategoryTitle"].toString();
        totalAttachmentCategoriesProbability += attachmentCategory["probability"].toDouble();
        ui->attachmentCategoriesLW->addItem(title);
    }
    ui->attachmentCategoriesTotalProbabilityValueLabel->setText(QString("%1").arg(totalAttachmentCategoriesProbability, 0, 'f', 5));

    totalAttachmentsProbability = 0.0;
    QJsonArray attachments = attachmentCategories[selectedAttachmentCategoryIndex].toObject()["attachments"].toArray();
    for (int i = 0; i < attachments.size(); i++)
    {
        QJsonObject attachment = attachments[i].toObject();
        QString title = attachment["attachmentClassName"].toString();
        totalAttachmentsProbability += attachment["probability"].toDouble();
        ui->attachmentsLW->addItem(title);
    }
    ui->attachmentsTotalProbabilityValueLabel->setText(QString("%1").arg(totalAttachmentsProbability, 0, 'f', 5));
}

void MainWindow::clearListWidget(QListWidget *listWidget)
{
    listWidget->blockSignals(true);
    listWidget->clear();
    listWidget->blockSignals(false);
}

void MainWindow::locationLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    clearListWidget(ui->categoriesLW);
    clearListWidget(ui->vehicleAttachmentsLW);

    ui->categoriesLE->clear();
    ui->itemsLE->clear();
    ui->vehicleAttachmentsLE->clear();

    selectedLocationIndex = ui->locationsLW->indexFromItem(current).row();

//    qDebug() << "Selected location at index " << selectedLocationIndex;

    QString locationTitle = current->text();
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();

    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject locationLoot = location["loot"].toObject();
    QJsonArray locationCoordinates = location["locationCoordinatesXYZ"].toArray();
    QJsonArray locationOrientation = location["locationOrientationYPR"].toArray();
    QJsonArray lootcrateCoordinates = location["lootcrateCoordinatesXYZ"].toArray();
    QJsonArray lootcrateOrientation = location["lootcrateOrientationYPR"].toArray();
    QJsonArray vehicleCoordinates = location["vehicleCoordinatesXYZ"].toArray();
    QJsonArray vehicleOrientation = location["vehicleOrientationYPR"].toArray();
    QJsonArray vehicleAttachments = location["vehicleAttachments"].toArray();
    totalCategoriesProbability = 0.0;

    for (int i = 0; i < vehicleAttachments.size(); i++)
    {
        QString attachment = vehicleAttachments[i].toString();
        ui->vehicleAttachmentsLW->addItem(attachment);
    }

    totalCategoriesProbability = 0.0;
    QJsonArray lootCategories = location["loot"].toObject()["lootCategories"].toArray();
    for (int i = 0; i < lootCategories.size(); i++)
    {
        QJsonObject category = lootCategories[i].toObject();
        QString title = category["lootCategoryTitle"].toString();
        totalCategoriesProbability += category["probability"].toDouble();
        ui->categoriesLW->addItem(title);
    }

    ui->categoriesTotalProbabilityValueLabel->setText(QString("%1").arg(totalCategoriesProbability, 0, 'f', 5));
    ui->locationNameLE->setText(location["locationTitle"].toString());
    ui->locationXCoordinateLE->setText(QString::number(locationCoordinates[0].toDouble(), 'f', 4));
    ui->locationYCoordinateLE->setText(QString::number(locationCoordinates[1].toDouble(), 'f', 4));
    ui->locationZCoordinateLE->setText(QString::number(locationCoordinates[2].toDouble(), 'f', 4));
    ui->locationYOrientationLE->setText(QString::number(locationOrientation[0].toDouble(), 'f', 4));
    ui->locationPOrientationLE->setText(QString::number(locationOrientation[1].toDouble(), 'f', 4));
    ui->locationROrientationLE->setText(QString::number(locationOrientation[2].toDouble(), 'f', 4));
    ui->locationLootcrateLE->setText(location["lootcrateClassName"].toString());
    ui->locationLootcrateXCoordinateLE->setText(QString::number(lootcrateCoordinates[0].toDouble(), 'f', 4));
    ui->locationLootcrateYCoordinateLE->setText(QString::number(lootcrateCoordinates[1].toDouble(), 'f', 4));
    ui->locationLootcrateZCoordinateLE->setText(QString::number(lootcrateCoordinates[2].toDouble(), 'f', 4));
    ui->locationLootcrateYOrientationLE->setText(QString::number(lootcrateOrientation[0].toDouble(), 'f', 4));
    ui->locationLootcratePOrientationLE->setText(QString::number(lootcrateOrientation[1].toDouble(), 'f', 4));
    ui->locationLootcrateROrientationLE->setText(QString::number(lootcrateOrientation[2].toDouble(), 'f', 4));
    ui->locationCaptureAreaRadiusSlider->setValue(location["captureAreaRadius"].toInt());
    ui->locationCaptureAreaHeightSlider->setValue(location["captureAreaHeight"].toInt());
    ui->locationCaptureAreaYOffsetSlider->setValue(location["captureAreaYAxisOffset"].toInt());
    ui->locationVehicleNameLE->setText(location["vehicleClassName"].toString());
    ui->locationVehicleXCoordinateLE->setText(QString::number(vehicleCoordinates[0].toDouble(), 'f', 4));
    ui->locationVehicleYCoordinateLE->setText(QString::number(vehicleCoordinates[1].toDouble(), 'f', 4));
    ui->locationVehicleZCoordinateLE->setText(QString::number(vehicleCoordinates[2].toDouble(), 'f', 4));
    ui->locationVehicleYOrientationLE->setText(QString::number(vehicleOrientation[0].toDouble(), 'f', 4));
    ui->locationVehiclePOrientationLE->setText(QString::number(vehicleOrientation[1].toDouble(), 'f', 4));
    ui->locationVehicleROrientationLE->setText(QString::number(vehicleOrientation[2].toDouble(), 'f', 4));
    ui->locationVehicleProbabilityDSB->setValue(location["vehicleProbability"].toDouble());
    ui->locationZombieCountSB->setValue(location["zombieCount"].toInt());
    ui->locationLootCountSB->setValue(locationLoot["lootCount"].toInt());
    ui->locationsLE->setText(locationTitle);

    setState(MainWindow::LocationSelected);
}

void MainWindow::categoryLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    clearListWidget(ui->itemsLW);

    ui->itemsLE->clear();

    selectedCategoryIndex = ui->categoriesLW->indexFromItem(current).row();

//    qDebug() << "Selected category at index " << selectedCategoryIndex;

    QString categoryTitle = current->text();
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject locationLoot = location["loot"].toObject();
    QJsonArray lootCategories = locationLoot["lootCategories"].toArray();
    QJsonObject category = lootCategories[selectedCategoryIndex].toObject();
    QJsonArray categoryItems = category["items"].toArray();
    totalItemsProbability = 0.0;

    for (int i = 0; i < categoryItems.size(); i++)
    {
        QJsonObject item = categoryItems[i].toObject();
        QString title = item["lootItemClassName"].toString();
        totalItemsProbability += item["probability"].toDouble();
        ui->itemsLW->addItem(title);
    }

    ui->itemsTotalProbabilityValueLabel->setText(QString("%1").arg(totalItemsProbability, 0, 'f', 5));
    ui->categoryNameLE->setText(category["lootCategoryTitle"].toString());
    ui->categoryProbabilityDSB->setValue(category["probability"].toDouble());
    ui->categoryLootLimitSB->setValue(category["limit"].toInt());
    ui->categoriesLE->setText(categoryTitle);

    setState(MainWindow::CategorySelected);
}

void MainWindow::itemLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    clearListWidget(ui->attachmentCategoriesLW);

    ui->attachmentCategoriesLE->clear();

    selectedItemIndex = ui->itemsLW->indexFromItem(current).row();

//    qDebug() << "Selected item at index " << selectedItemIndex;

    QString itemTitle = current->text();
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject locationLoot = location["loot"].toObject();
    QJsonArray lootCategories = locationLoot["lootCategories"].toArray();
    QJsonObject category = lootCategories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();
    QJsonArray attachmentCategories = item["attachmentCategories"].toArray();
    totalAttachmentCategoriesProbability = 0.0;

    for (int i = 0; i < attachmentCategories.size(); i++)
    {
        QJsonObject attachmentCategory = attachmentCategories[i].toObject();
        QString title = attachmentCategory["attachmentCategoryTitle"].toString();
        double probability = attachmentCategory["probability"].toDouble();
        if (probability < 1.0)
        {
            totalAttachmentCategoriesProbability += probability;
        }

        ui->attachmentCategoriesLW->addItem(title);
    }

    ui->attachmentCategoriesTotalProbabilityValueLabel->setText(QString("%1").arg(totalAttachmentCategoriesProbability, 0, 'f', 5));
    ui->itemNameLE->setText(item["lootItemClassName"].toString());
    ui->itemProbabilityDSB->setValue(item["probability"].toDouble());
    ui->itemQuantitySB->setValue(item["quantity"].toInt());
    ui->categoryLootRandomizeQuantityCheckBox->setChecked(item["hasRandomQuantity"].toBool());
    ui->itemsLE->setText(itemTitle);

    setState(MainWindow::ItemSelected);
}

void MainWindow::attachmentCategoryLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    clearListWidget(ui->attachmentsLW);

    ui->attachmentsLE->clear();

    selectedAttachmentCategoryIndex = ui->attachmentCategoriesLW->indexFromItem(current).row();

//    qDebug() << "Selected attachment category at index " << selectedAttachmentCategoryIndex;

    QString attachmentCategoryTitle = current->text();
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject locationLoot = location["loot"].toObject();
    QJsonArray lootCategories = locationLoot["lootCategories"].toArray();
    QJsonObject category = lootCategories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();
    QJsonArray attachmentCategories = item["attachmentCategories"].toArray();
    QJsonObject attachmentCategory = attachmentCategories[selectedAttachmentCategoryIndex].toObject();
    QJsonArray attachments = attachmentCategory["attachments"].toArray();

    totalAttachmentsProbability = 0.0;
    for (int i = 0; i < attachments.size(); i++)
    {
        QJsonObject attachment = attachments[i].toObject();
        QString title = attachment["attachmentClassName"].toString();
        totalAttachmentsProbability += attachment["probability"].toDouble();
        ui->attachmentsLW->addItem(title);
    }

    double probability = attachmentCategory["probability"].toDouble();
    if (probability < 1.0)
    {
        ui->attachmentCategoryProbabilityInfoLabel->clear();
    }
    else
    {
        ui->attachmentCategoryProbabilityInfoLabel->setText("Excluded from total probability");
    }

    ui->attachmentsTotalProbabilityValueLabel->setText(QString("%1").arg(totalAttachmentsProbability, 0, 'f', 5));
    ui->attachmentCategoryNameLE->setText(attachmentCategory["attachmentCategoryTitle"].toString());
    ui->attachmentCategoryProbabilityDSB->setValue(attachmentCategory["probability"].toDouble());
    ui->attachmentCategoriesLE->setText(attachmentCategoryTitle);

    setState(MainWindow::AttachmentCategorySelected);
}

void MainWindow::attachmentLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    selectedAttachmentIndex = ui->attachmentsLW->indexFromItem(current).row();

//    qDebug() << "Selected attachment at index " << selectedAttachmentIndex;

    QString attachmentTitle = current->text();
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject locationLoot = location["loot"].toObject();
    QJsonArray lootCategories = locationLoot["lootCategories"].toArray();
    QJsonObject category = lootCategories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();
    QJsonArray attachmentCategories = item["attachmentCategories"].toArray();
    QJsonObject attachmentCategory = attachmentCategories[selectedAttachmentCategoryIndex].toObject();
    QJsonArray attachments = attachmentCategory["attachments"].toArray();
    QJsonObject attachment = attachments[selectedAttachmentIndex].toObject();

    ui->attachmentNameLE->setText(attachment["attachmentClassName"].toString());
    ui->attachmentProbabilityDSB->setValue(attachment["probability"].toDouble());
    ui->attachmentsLE->setText(attachmentTitle);

    setState(MainWindow::AttachmentSelected);
}

void MainWindow::vehicleAttachmentLWItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->vehicleAttachmentsLE->setText(current->text());
}

void MainWindow::addVehicleAttachmentBtnClicked()
{
    QString text = ui->vehicleAttachmentsLE->text();
    if (text.isEmpty()) return;

    QJsonArray locations, vehicleAttachments;
    QJsonObject location;
    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    vehicleAttachments = location["vehicleAttachments"].toArray();

    vehicleAttachments.append(QJsonValue::fromVariant(text));

    location["vehicleAttachments"] = vehicleAttachments;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::deleteVehicleAttachmentBtnClicked()
{
    QJsonArray locations, vehicleAttachments;
    QJsonObject location;
    QList<QListWidgetItem *> selectedVehicleAttachments = ui->vehicleAttachmentsLW->selectedItems();
    QList<int> deleteIndexes = {};

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    vehicleAttachments = location["vehicleAttachments"].toArray();

    for (int i = 0; i < selectedVehicleAttachments.size(); i++)
    {
        deleteIndexes.append(ui->vehicleAttachmentsLW->indexFromItem(selectedVehicleAttachments[i]).row());
    }

    std::sort(deleteIndexes.begin(), deleteIndexes.end());
    std::reverse(deleteIndexes.begin(), deleteIndexes.end());

    for (int i = 0; i < deleteIndexes.size(); i++)
    {
        vehicleAttachments.removeAt(deleteIndexes[i]);
    }

    location["vehicleAttachments"] = vehicleAttachments;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    ui->vehicleAttachmentsLE->clear();
    this->refreshView();
}

void MainWindow::copyVehicleAttachmentBtnClicked()
{
    QJsonArray locations, vehicleAttachments;
    QJsonObject location;
    QList<QListWidgetItem *> selectedVehicleAttachments = ui->vehicleAttachmentsLW->selectedItems();

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    vehicleAttachments = location["vehicleAttachments"].toArray();

    copiedVehicleAttachments = {};
    for (int i = 0; i < selectedVehicleAttachments.size(); i++)
    {
        int index = ui->vehicleAttachmentsLW->indexFromItem(selectedVehicleAttachments[i]).row();

        copiedVehicleAttachments.append(vehicleAttachments[index]);
    }
}

void MainWindow::pasteVehicleAttachmentBtnClicked()
{
    QJsonArray locations, vehicleAttachments;
    QJsonObject location;

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    vehicleAttachments = location["vehicleAttachments"].toArray();

    foreach (auto vehicleAttachment, copiedVehicleAttachments) {
        vehicleAttachments.append(vehicleAttachment);
    }

    location["vehicleAttachments"] = vehicleAttachments;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::radiusSliderValueChanged(int value)
{
    ui->locationCaptureAreaRadiusSliderValueLabel->setText(QString::number(value));
}

void MainWindow::heightSliderValueChanged(int value)
{
    ui->locationCaptureAreaHeightSliderValueLabel->setText(QString::number(value));
}

void MainWindow::YOffsetSliderValueChanged(int value)
{
    ui->locationCaptureAreaYOffsetSliderValueLabel->setText(QString::number(value));
}

void MainWindow::addCategoryBtnClicked()
{
    QString text = ui->categoriesLE->text();
    if (text.isEmpty()) return;

    QJsonArray locations, lootCategories;
    QJsonObject location, loot, category;
    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();

    category.insert("lootCategoryTitle", QJsonValue::fromVariant(text));
    category.insert("probability", QJsonValue::fromVariant(0));
    category.insert("limit", QJsonValue::fromVariant(0));
    category.insert("items", QJsonValue::fromVariant(QJsonArray()));

    lootCategories.append(category);
    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::deleteCategoryBtnClicked()
{
    QJsonArray locations, lootCategories;
    QJsonObject location, loot, category;
    QList<QListWidgetItem *> selectedCategories = ui->categoriesLW->selectedItems();
    QList<int> deleteIndexes = {};

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();

    for (int i = 0; i < selectedCategories.size(); i++)
    {
        deleteIndexes.append(ui->categoriesLW->indexFromItem(selectedCategories[i]).row());
    }

    std::sort(deleteIndexes.begin(), deleteIndexes.end());
    std::reverse(deleteIndexes.begin(), deleteIndexes.end());

    for (int i = 0; i < deleteIndexes.size(); i++)
    {
        lootCategories.removeAt(deleteIndexes[i]);
    }

    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    ui->categoriesLE->clear();
    this->refreshView();
    setState(MainWindow::CategoryUnselected);
}

void MainWindow::copyCategoryBtnClicked()
{
    QJsonArray locations, lootCategories;
    QJsonObject location, loot, category;
    QList<QListWidgetItem *> selectedCategories = ui->categoriesLW->selectedItems();

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();

    copiedCategories = {};
    for (int i = 0; i < selectedCategories.size(); i++)
    {
        int index = ui->categoriesLW->indexFromItem(selectedCategories[i]).row();

        copiedCategories.append(lootCategories[index]);
    }
}

void MainWindow::pasteCategoryBtnClicked()
{
    QJsonArray locations, lootCategories;
    QJsonObject location, loot, category;

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();

    foreach (auto category, copiedCategories)
    {
        lootCategories.append(category);
    }

    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::addItemBtnClicked()
{
    QString text = ui->itemsLE->text();
    if (text.isEmpty()) return;

    QJsonArray locations, lootCategories, items;
    QJsonObject location, loot, category, item;

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();

    item.insert("lootItemClassName", QJsonValue::fromVariant(text));
    item.insert("probability", QJsonValue::fromVariant(0));
    item.insert("quantity", QJsonValue::fromVariant(1));
    item.insert("attachmentCategories", QJsonValue::fromVariant(QJsonArray()));
    items.append(item);

    category["items"] = items;
    lootCategories[selectedCategoryIndex] = category;
    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::deleteItemBtnClicked()
{
    QJsonArray locations, lootCategories, items;
    QJsonObject location, loot, category, item;
    QList<QListWidgetItem *> selectedCategoryLoot = ui->itemsLW->selectedItems();
    QList<int> deleteIndexes = {};

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();

    for (int i = 0; i < selectedCategoryLoot.size(); i++)
    {
        deleteIndexes.append(ui->itemsLW->indexFromItem(selectedCategoryLoot[i]).row());
    }

    std::sort(deleteIndexes.begin(), deleteIndexes.end());
    std::reverse(deleteIndexes.begin(), deleteIndexes.end());

    for (int i = 0; i < deleteIndexes.size(); i++)
    {
        items.removeAt(deleteIndexes[i]);
    }

    category["items"] = items;
    lootCategories[selectedCategoryIndex] = category;
    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    ui->itemsLE->clear();
    this->refreshView();
    setState(MainWindow::ItemUnselected);
}

void MainWindow::copyItemBtnClicked()
{
    QJsonArray locations, lootCategories, items;
    QJsonObject location, loot, category, item;
    QList<QListWidgetItem *> selectedItems = ui->itemsLW->selectedItems();

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();

    copiedItems = {};
    for (int i = 0; i < selectedItems.size(); i++)
    {
        int index = ui->itemsLW->indexFromItem(selectedItems[i]).row();

        copiedItems.append(items[index]);
    }
}

void MainWindow::pasteItemBtnClicked()
{
    QJsonArray locations, lootCategories, items;
    QJsonObject location, loot, category, item;

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();

    foreach (auto item, copiedItems)
    {
        items.append(item);
    }

    category["items"] = items;
    lootCategories[selectedCategoryIndex] = category;
    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::addAttachmentCategoryBtnClicked()
{
    QString text = ui->attachmentCategoriesLE->text();
    if (text.isEmpty()) return;

    QJsonArray locations, lootCategories, items, attachmentCategories;
    QJsonObject location, loot, category, item, attachmentCategory;

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();
    item = items[selectedItemIndex].toObject();
    attachmentCategories = item["attachmentCategories"].toArray();

    attachmentCategory.insert("attachmentCategoryTitle", QJsonValue::fromVariant(text));
    attachmentCategory.insert("probability", QJsonValue::fromVariant(0));
    attachmentCategory.insert("attachments", QJsonValue::fromVariant(QJsonArray()));
    attachmentCategories.append(attachmentCategory);

    item["attachmentCategories"] = attachmentCategories;
    items[selectedItemIndex] = item;
    category["items"] = items;
    lootCategories[selectedCategoryIndex] = category;
    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::addAttachmentBtnClicked()
{
    QString text = ui->attachmentsLE->text();
    if (text.isEmpty()) return;

    QJsonArray locations, lootCategories, items, attachmentCategories, attachments;
    QJsonObject location, loot, category, item, attachmentCategory, attachment;

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();
    item = items[selectedItemIndex].toObject();
    attachmentCategories = item["attachmentCategories"].toArray();
    attachmentCategory = attachmentCategories[selectedAttachmentCategoryIndex].toObject();
    attachments = attachmentCategory["attachments"].toArray();

    attachment.insert("attachmentClassName", QJsonValue::fromVariant(text));
    attachment.insert("probability", QJsonValue::fromVariant(0));
    attachments.append(attachment);

    attachmentCategory["attachments"] = attachments;
    attachmentCategories[selectedAttachmentCategoryIndex] = attachmentCategory;
    item["attachmentCategories"] = attachmentCategories;
    items[selectedItemIndex] = item;
    category["items"] = items;
    lootCategories[selectedCategoryIndex] = category;
    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::deleteAttachmentCategoryBtnClicked()
{
    QJsonArray locations, lootCategories, items, attachmentCategories;
    QJsonObject location, loot, category, item, attachemtnCategory;
    QList<QListWidgetItem *> selectedAttachmentCategories = ui->attachmentCategoriesLW->selectedItems();
    QList<int> deleteIndexes = {};

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();
    item = items[selectedItemIndex].toObject();
    attachmentCategories = item["attachmentCategories"].toArray();

    for (int i = 0; i < selectedAttachmentCategories.size(); i++)
    {
        deleteIndexes.append(ui->attachmentCategoriesLW->indexFromItem(selectedAttachmentCategories[i]).row());
    }

    std::sort(deleteIndexes.begin(), deleteIndexes.end());
    std::reverse(deleteIndexes.begin(), deleteIndexes.end());

    for (int i = 0; i < deleteIndexes.size(); i++)
    {
        attachmentCategories.removeAt(deleteIndexes[i]);
    }

    item["attachmentCategories"] = attachmentCategories;
    items[selectedItemIndex] = item;
    category["items"] = items;
    lootCategories[selectedCategoryIndex] = category;
    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    ui->attachmentCategoriesLE->clear();
    this->refreshView();
    setState(MainWindow::AttachmentCategoryUnselected);
}

void MainWindow::deleteAttachmentBtnClicked()
{
    QJsonArray locations, lootCategories, items, attachmentCategories, attachments;
    QJsonObject location, loot, category, item, attachmentCategory, attachment;
    QList<QListWidgetItem *> selectedAttachments = ui->attachmentsLW->selectedItems();
    QList<int> deleteIndexes = {};

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();
    item = items[selectedItemIndex].toObject();
    attachmentCategories = item["attachmentCategories"].toArray();
    attachmentCategory = attachmentCategories[selectedAttachmentCategoryIndex].toObject();
    attachments = attachmentCategory["attachments"].toArray();

    for (int i = 0; i < selectedAttachments.size(); i++)
    {
        deleteIndexes.append(ui->attachmentsLW->indexFromItem(selectedAttachments[i]).row());
    }

    std::sort(deleteIndexes.begin(), deleteIndexes.end());
    std::reverse(deleteIndexes.begin(), deleteIndexes.end());

    for (int i = 0; i < deleteIndexes.size(); i++)
    {
        attachments.removeAt(deleteIndexes[i]);
    }

    attachmentCategory["attachments"] = attachments;
    attachmentCategories[selectedAttachmentCategoryIndex] = attachmentCategory;
    item["attachmentCategories"] = attachmentCategories;
    items[selectedItemIndex] = item;
    category["items"] = items;
    lootCategories[selectedCategoryIndex] = category;
    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    ui->attachmentsLE->clear();
    this->refreshView();
    setState(MainWindow::AttachmentUnselected);
}

void MainWindow::copyAttachmentCategoryBtnClicked()
{
    QJsonArray locations, lootCategories, items, attachmentCategories;
    QJsonObject location, loot, category, item, attachemtnCategory;
    QList<QListWidgetItem *> selectedAttachmentCategories = ui->attachmentCategoriesLW->selectedItems();

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();
    item = items[selectedItemIndex].toObject();
    attachmentCategories = item["attachmentCategories"].toArray();

    copiedAttachmentCategories = {};
    for (int i = 0; i < selectedAttachmentCategories.size(); i++)
    {
        int index = ui->attachmentCategoriesLW->indexFromItem(selectedAttachmentCategories[i]).row();

        copiedAttachmentCategories.append(attachmentCategories[index]);
    }
}

void MainWindow::pasteAttachmentCategoryBtnClicked()
{
    QJsonArray locations, lootCategories, items, attachmentCategories;
    QJsonObject location, loot, category, item, attachemtnCategory;

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();
    item = items[selectedItemIndex].toObject();
    attachmentCategories = item["attachmentCategories"].toArray();

    foreach (auto attachmentCategory, copiedAttachmentCategories)
    {
        attachmentCategories.append(attachmentCategory);
    }

    item["attachmentCategories"] = attachmentCategories;
    items[selectedItemIndex] = item;
    category["items"] = items;
    lootCategories[selectedCategoryIndex] = category;
    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::copyAttachmentBtnClicked()
{
    QJsonArray locations, lootCategories, items, attachmentCategories, attachments;
    QJsonObject location, loot, category, item, attachmentCategory, attachment;
    QList<QListWidgetItem *> selectedAttachments = ui->attachmentsLW->selectedItems();

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();
    item = items[selectedItemIndex].toObject();
    attachmentCategories = item["attachmentCategories"].toArray();
    attachmentCategory = attachmentCategories[selectedAttachmentCategoryIndex].toObject();
    attachments = attachmentCategory["attachments"].toArray();

    copiedAttachments = {};
    for (int i = 0; i < selectedAttachments.size(); i++)
    {
        int index = ui->attachmentsLW->indexFromItem(selectedAttachments[i]).row();

        copiedAttachments.append(attachments[index]);
    }
}

void MainWindow::pasteAttachmentBtnClicked()
{
    QJsonArray locations, lootCategories, items, attachmentCategories, attachments;
    QJsonObject location, loot, category, item, attachmentCategory, attachment;

    locations = jsonRootObj["eventLocations"].toArray();
    location = locations[selectedLocationIndex].toObject();
    loot = location["loot"].toObject();
    lootCategories = loot["lootCategories"].toArray();
    category = lootCategories[selectedCategoryIndex].toObject();
    items = category["items"].toArray();
    item = items[selectedItemIndex].toObject();
    attachmentCategories = item["attachmentCategories"].toArray();
    attachmentCategory = attachmentCategories[selectedAttachmentCategoryIndex].toObject();
    attachments = attachmentCategory["attachments"].toArray();

    foreach (auto attachment, copiedAttachments)
    {
        attachments.append(attachment);
    }

    attachmentCategory["attachments"] = attachments;
    attachmentCategories[selectedAttachmentCategoryIndex] = attachmentCategory;
    item["attachmentCategories"] = attachmentCategories;
    items[selectedItemIndex] = item;
    category["items"] = items;
    lootCategories[selectedCategoryIndex] = category;
    loot["lootCategories"] = lootCategories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    this->refreshView();
}

void MainWindow::locationNameLETextChanged(const QString &arg1)
{
    ui->locationsLW->item(selectedLocationIndex)->setText(arg1);

    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();

    location["locationTitle"] = arg1;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationXCoordinateLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray locationCoordinates = location["locationCoordinatesXYZ"].toArray();

    locationCoordinates[0] = arg1.toDouble();
    location["locationCoordinatesXYZ"] = locationCoordinates;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationYCoordinateLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray locationCoordinates = location["locationCoordinatesXYZ"].toArray();

    locationCoordinates[1] = arg1.toDouble();
    location["locationCoordinatesXYZ"] = locationCoordinates;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationZCoordinateLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray locationCoordinates = location["locationCoordinatesXYZ"].toArray();

    locationCoordinates[2] = arg1.toDouble();
    location["locationCoordinatesXYZ"] = locationCoordinates;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationYOrientationLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray locationOrientation = location["locationOrientationYPR"].toArray();

    locationOrientation[0] = arg1.toDouble();
    location["locationOrientationYPR"] = locationOrientation;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationPOrientationLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray locationOrientation = location["locationOrientationYPR"].toArray();

    locationOrientation[1] = arg1.toDouble();
    location["locationOrientationYPR"] = locationOrientation;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationROrientationLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray locationOrientation = location["locationOrientationYPR"].toArray();

    locationOrientation[2] = arg1.toDouble();
    location["locationOrientationYPR"] = locationOrientation;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationLootcrateClassNameLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();

    location["lootcrateClassName"] = arg1;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationLootcrateXCoordinateLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray lootcrateCoordinates = location["lootcrateCoordinatesXYZ"].toArray();

    lootcrateCoordinates[0] = arg1.toDouble();
    location["lootcrateCoordinatesXYZ"] = lootcrateCoordinates;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationLootcrateYCoordinateLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray lootcrateCoordinates = location["lootcrateCoordinatesXYZ"].toArray();

    lootcrateCoordinates[1] = arg1.toDouble();
    location["lootcrateCoordinatesXYZ"] = lootcrateCoordinates;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationLootcrateZCoordinateLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray lootcrateCoordinates = location["lootcrateCoordinatesXYZ"].toArray();

    lootcrateCoordinates[2] = arg1.toDouble();
    location["lootcrateCoordinatesXYZ"] = lootcrateCoordinates;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationLootcrateYOrientationLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray lootcrateOrientation = location["lootcrateOrientationYPR"].toArray();

    lootcrateOrientation[0] = arg1.toDouble();
    location["lootcrateOrientationYPR"] = lootcrateOrientation;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationLootcratePOrientationLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray lootcrateOrientation = location["lootcrateOrientationYPR"].toArray();

    lootcrateOrientation[1] = arg1.toDouble();
    location["lootcrateOrientationYPR"] = lootcrateOrientation;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationLootcrateROrientationLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray lootcrateOrientation = location["lootcrateOrientationYPR"].toArray();

    lootcrateOrientation[2] = arg1.toDouble();
    location["lootcrateOrientationYPR"] = lootcrateOrientation;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationCaptureAreaRadiusSliderValueChanged(int value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();

    location["captureAreaRadius"] = value;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationCaptureAreaHeightSliderValueChanged(int value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();

    location["captureAreaHeight"] = value;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationCaptureAreaYOffsetSliderValueChanged(int value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();

    location["captureAreaYAxisOffset"] = value;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationVehicleClassNameLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();

    location["vehicleClassName"] = arg1;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationVehicleXCoordinateLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray vehicleCoordinates = location["vehicleCoordinatesXYZ"].toArray();

    vehicleCoordinates[0] = arg1.toDouble();
    location["vehicleCoordinatesXYZ"] = vehicleCoordinates;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationVehicleYCoordinateLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray vehicleCoordinates = location["vehicleCoordinatesXYZ"].toArray();

    vehicleCoordinates[1] = arg1.toDouble();
    location["vehicleCoordinatesXYZ"] = vehicleCoordinates;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationVehicleZCoordinateLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray vehicleCoordinates = location["vehicleCoordinatesXYZ"].toArray();

    vehicleCoordinates[2] = arg1.toDouble();
    location["vehicleCoordinatesXYZ"] = vehicleCoordinates;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationVehicleYOrientationLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray vehicleOrientation = location["vehicleOrientationYPR"].toArray();

    vehicleOrientation[0] = arg1.toDouble();
    location["vehicleOrientationYPR"] = vehicleOrientation;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationVehiclePOrientationLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray vehicleOrientation = location["vehicleOrientationYPR"].toArray();

    vehicleOrientation[1] = arg1.toDouble();
    location["vehicleOrientationYPR"] = vehicleOrientation;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationVehicleROrientationLETextChanged(const QString &arg1)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonArray vehicleOrientation = location["vehicleOrientationYPR"].toArray();

    vehicleOrientation[2] = arg1.toDouble();
    location["vehicleOrientationYPR"] = vehicleOrientation;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationVehicleProbabilityDSBValueChanged(double value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();

    location["vehicleProbability"] = value;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationZombieCountSBValueChanged(int value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();

    location["zombieCount"] = value;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::locationLootCountSBValueChanged(int value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();

    loot["lootCount"] = value;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::categoryNameLETextChanged(const QString &arg1)
{
    ui->categoriesLW->item(selectedCategoryIndex)->setText(arg1);

    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();

    category["lootCategoryTitle"] = arg1;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::categoryProbabilityDSBValueChanged(double value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();

    totalCategoriesProbability -= (category["probability"].toDouble() - value);
    category["probability"] = value;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    ui->categoriesTotalProbabilityValueLabel->setText(QString("%1").arg(totalCategoriesProbability, 0, 'f', 5));
}

void MainWindow::categoryLootLimitSBValueChanged(int value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();

    category["limit"] = value;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::itemClassNameLETextChanged(const QString &arg1)
{
    ui->itemsLW->item(selectedItemIndex)->setText(arg1);

    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();

    item["lootItemClassName"] = arg1;
    items[selectedItemIndex] = item;
    category["items"] = items;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::itemProbabilityDSBValueChanged(double value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();

    totalItemsProbability -= (item["probability"].toDouble() - value);
    item["probability"] = value;
    items[selectedItemIndex] = item;
    category["items"] = items;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    ui->itemsTotalProbabilityValueLabel->setText(QString("%1").arg(totalItemsProbability, 0, 'f', 5));
}

void MainWindow::itemQuantitySBValueChanged(int value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();

    item["quantity"] = value;
    items[selectedItemIndex] = item;
    category["items"] = items;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::attachmentCategoryNameLETextChanged(const QString &arg1)
{
    ui->attachmentCategoriesLW->item(selectedAttachmentCategoryIndex)->setText(arg1);

    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();
    QJsonArray attachmentCategories = item["attachmentCategories"].toArray();
    QJsonObject attachmentCategory = attachmentCategories[selectedAttachmentCategoryIndex].toObject();

    attachmentCategory["attachmentCategoryTitle"] = arg1;
    attachmentCategories[selectedAttachmentCategoryIndex] = attachmentCategory;
    item["attachmentCategories"] = attachmentCategories;
    items[selectedItemIndex] = item;
    category["items"] = items;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::attachmentCategoryProbabilityDSBValueChanged(double value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();
    QJsonArray attachmentCategories = item["attachmentCategories"].toArray();
    QJsonObject attachmentCategory = attachmentCategories[selectedAttachmentCategoryIndex].toObject();

//    totalAttachmentCategoriesProbability -= (attachmentCategory["probability"].toDouble() - value);
    double oldProbability = attachmentCategory["probability"].toDouble();
    if (value < 1.0)
    {
        // Subtract the old probability only if it was less than 1.0
        totalAttachmentCategoriesProbability -= (oldProbability < 1.0 ? oldProbability : 0);
        totalAttachmentCategoriesProbability += value;
        ui->attachmentCategoryProbabilityInfoLabel->clear();
    }
    else if (oldProbability < 1.0)
    {
        // If the old probability was less than 1.0, subtract it
        totalAttachmentCategoriesProbability -= oldProbability;
        ui->attachmentCategoryProbabilityInfoLabel->setText("Excluded from total probability");
    }

    attachmentCategory["probability"] = value;
    attachmentCategories[selectedAttachmentCategoryIndex] = attachmentCategory;
    item["attachmentCategories"] = attachmentCategories;
    items[selectedItemIndex] = item;
    category["items"] = items;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    ui->attachmentCategoriesTotalProbabilityValueLabel->setText(QString("%1").arg(totalAttachmentCategoriesProbability, 0, 'f', 5));
}

void MainWindow::attachmentClassNameLETextChanged(const QString &arg1)
{
    ui->attachmentsLW->item(selectedAttachmentIndex)->setText(arg1);

    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();
    QJsonArray attachmentCategories = item["attachmentCategories"].toArray();
    QJsonObject attachmentCategory = attachmentCategories[selectedAttachmentCategoryIndex].toObject();
    QJsonArray attachments = attachmentCategory["attachments"].toArray();
    QJsonObject attachment = attachments[selectedAttachmentIndex].toObject();

    attachment["attachmentClassName"] = arg1;
    attachments[selectedAttachmentIndex] = attachment;
    attachmentCategory["attachments"] = attachments;
    attachmentCategories[selectedAttachmentCategoryIndex] = attachmentCategory;
    item["attachmentCategories"] = attachmentCategories;
    items[selectedItemIndex] = item;
    category["items"] = items;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;
}

void MainWindow::attachmentProbabilityDSBValueChanged(double value)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();
    QJsonArray attachmentCategories = item["attachmentCategories"].toArray();
    QJsonObject attachmentCategory = attachmentCategories[selectedAttachmentCategoryIndex].toObject();
    QJsonArray attachments = attachmentCategory["attachments"].toArray();
    QJsonObject attachment = attachments[selectedAttachmentIndex].toObject();

    totalAttachmentsProbability -= (attachment["probability"].toDouble() - value);
    attachment["probability"] = value;
    attachments[selectedAttachmentIndex] = attachment;
    attachmentCategory["attachments"] = attachments;
    attachmentCategories[selectedAttachmentCategoryIndex] = attachmentCategory;
    item["attachmentCategories"] = attachmentCategories;
    items[selectedItemIndex] = item;
    category["items"] = items;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    ui->attachmentsTotalProbabilityValueLabel->setText(QString("%1").arg(totalAttachmentsProbability, 0, 'f', 5));
}

void MainWindow::categoryLootRandomizeQuantityCheckBoxClicked(bool checked)
{
    QJsonArray locations = jsonRootObj["eventLocations"].toArray();
    QJsonObject location = locations[selectedLocationIndex].toObject();
    QJsonObject loot = location["loot"].toObject();
    QJsonArray categories = loot["lootCategories"].toArray();
    QJsonObject category = categories[selectedCategoryIndex].toObject();
    QJsonArray items = category["items"].toArray();
    QJsonObject item = items[selectedItemIndex].toObject();

//    if (checked)
//    {
//        item["HasRandomQuantity"] = checked;
//    }
//    else
//    {
//        item.remove("HasRandomQuantity");

//    }


    item["hasRandomQuantity"] = checked;
    items[selectedItemIndex] = item;
    category["items"] = items;
    categories[selectedCategoryIndex] = category;
    loot["lootCategories"] = categories;
    location["loot"] = loot;
    locations[selectedLocationIndex] = location;
    jsonRootObj["eventLocations"] = locations;

    if (checked)
    {
        if (ui->itemQuantitySB->value() <= 0)
        {
            ui->itemQuantitySB->setValue(1);
        }
    }
}
