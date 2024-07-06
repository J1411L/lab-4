#ifndef GAMELOGIC
#define GAMELOGIC

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QPainter>
#include <QColor>
#include <QPixmap>  // Добавляем этот include

// графическое оконное приложение
// Класс GameLogic, наследующий от QWidget, представляет логику игры "Змейка"
class GameLogic : public QWidget{
public:
    GameLogic(); // Конструктор класса GameLogic

protected:
    // Переопределенные виртуальные функции для обработки событий
    void timerEvent(QTimerEvent*) override; // Обработчик событий таймера
    void keyPressEvent(QKeyEvent*) override; // Обработчик события нажатия клавиши
    void paintEvent(QPaintEvent*) override; // Обработчик события перерисовки

private:
    // Константы, определяющие размеры змейки и игрового поля
    static const int SNAKE_WIDTH = 20;
    static const int SNAKE_HEIGHT = 20;
    static const int FIELD_WIDTH = 40;
    static const int FIELD_HEIGHT = 40;

    // Задержка между перемещениями змейки в миллисекундах
    int DELAY = 130;

    // Идентификатор таймера
    int TIMER_ID;

    // Перечисление направлений движения змейки
    enum Dirs{left, right, up, down};

    // Текущее направление движения змейки
    Dirs m_dir;

    // Флаг, указывающий, находится ли игра в процессе
    bool m_inGame;

    // Вектор, хранящий координаты сегментов змейки
    QVector<QPoint> m_dots;

    // Вектор, хранящий цвета сегментов змейки
    QVector<QColor> m_colors {Qt::red, Qt::yellow, Qt::blue, Qt::white};

    // Координаты яблока
    QPoint m_apple;

    // Переменные для хранения изображений
    QPixmap backgroundPixmap;  // Объявление переменной для фонового изображения
    QPixmap applePixmap;       // Переменная для изображения яблока

    // Приватные функции, реализующие логику игры
    void _INIT_GAME(); // Инициализация игры
    void _DRAWING(); // Отрисовка змейки и яблока
    void _DRAW_APPLE(); // Отрисовка яблока
    void _SNAKE_MOVE(); // Перемещение змейки
    void _CHECK_FIELD_EXIT(); // Проверка на выход змейки за пределы поля
    void _GAME_OVER(); // Обработка окончания игры
    void _CHECK_APPLE(); // Проверка на сбор яблока
};

#endif // GAMELOGIC
