#ifndef MENU_H
#define MENU_H

#include "gamelogic.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

// Класс Menu, наследующий от QMainWindow, представляет главное меню игры
class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr); // Конструктор класса Menu
    ~Menu(); // Деструктор класса Menu

private slots:
    // Слоты для обработки событий нажатия кнопок
    void on_QuitButton_clicked(); // Обработчик нажатия кнопки "Выйти"
    void on_PlayButton_clicked(); // Обработчик нажатия кнопки "Играть"

private:
    Ui::Menu *ui; // Указатель на объект пользовательского интерфейса
    GameLogic* game; // Указатель на объект класса GameLogic
};

#endif // MENU_H
