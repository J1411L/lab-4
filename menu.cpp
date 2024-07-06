#include "menu.h"
#include "ui_menu.h"

// Класс Menu является производным от класса QMainWindow, который является базовым классом для всех приложений главного окна в среде Qt.
Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    // Функция setupUi используется для настройки пользовательского интерфейса класса Menu на основе дизайна пользовательского интерфейса, определенного в файле «menu.ui».
    ui->setupUi(this);

    // Новый экземпляр класса GameLogic создается и сохраняется в переменной-члене game.
    game = new GameLogic();
}

// Деструктор класса Menu, отвечающий за удаление объекта пользовательского интерфейса.
Menu::~Menu()
{
    delete ui;
}

// Эта функция вызывается при нажатии кнопки «QuitButton». Закрывает текущее окно.
void Menu::on_QuitButton_clicked()
{
    this->close();
}

// Эта функция вызывается при нажатии кнопки «PlayButton». Он показывает окно игры и закрывает текущее окно.
void Menu::on_PlayButton_clicked()
{
    game->show();
    this->close();
}
