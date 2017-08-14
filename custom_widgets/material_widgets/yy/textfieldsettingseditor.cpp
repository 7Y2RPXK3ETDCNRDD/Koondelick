#include "textfieldsettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include "../components/textfield.h"
#include "../xx/qtmaterialtextfield.h"

TextFieldSettingsEditor::TextFieldSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::TextFieldSettingsForm),
      m_textField(new QtMaterialTextField)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    layout->addWidget(m_textField);
    layout->setAlignment(m_textField, Qt::AlignCenter);

    //TextField *tf = new TextField;
    //layout->addWidget(tf);
    //tf->setMinimumWidth(250);
    //tf->setPlaceholderText("A placeholder is this text");
    //tf->setLabel("This is the label");
    //layout->setAlignment(tf, Qt::AlignCenter);

    m_textField->setLabel("Wat is this");
    m_textField->setMinimumWidth(250);

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->textLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui->placeholderLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui->labelCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->labelTextLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->textColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->inkColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->underlineColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->labelColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    connect(m_textField, SIGNAL(textChanged(QString)), this, SLOT(setupForm()));
}

TextFieldSettingsEditor::~TextFieldSettingsEditor()
{
    delete ui;
}

void TextFieldSettingsEditor::setupForm()
{
    ui->disabledCheckBox->setChecked(!m_textField->isEnabled());
    ui->textLineEdit->setText(m_textField->text());
    ui->placeholderLineEdit->setText(m_textField->placeholderText());
    ui->labelCheckBox->setChecked(m_textField->hasLabel());
    ui->labelTextLineEdit->setText(m_textField->label());
    ui->useThemeColorsCheckBox->setChecked(m_textField->useThemeColors());
}

void TextFieldSettingsEditor::updateWidget()
{
    m_textField->setDisabled(ui->disabledCheckBox->isChecked());
    m_textField->setText(ui->textLineEdit->text());
    m_textField->setPlaceholderText(ui->placeholderLineEdit->text());
    m_textField->setLabel(ui->labelTextLineEdit->text());
    m_textField->setShowLabel(ui->labelCheckBox->isChecked());
    m_textField->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void TextFieldSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("textColorToolButton" == senderName) {
            m_textField->setTextColor(color);
            ui->textColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("inkColorToolButton" == senderName) {
            m_textField->setInkColor(color);
            ui->inkColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("underlineColorToolButton" == senderName) {
            m_textField->setUnderlineColor(color);
            ui->underlineColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("labelColorToolButton" == senderName) {
            m_textField->setLabelColor(color);
            ui->labelColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
