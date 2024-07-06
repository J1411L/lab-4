#include "gamelogic.h"

#include <QKeyEvent>
#include <QTime>
#include <QMessageBox>
#include <cstdlib>

GameLogic::GameLogic() {
    // Устанавливаем размер игрового окна в соответствии с размером поля и размером каждого сегмента змейки
    // SNAKE_WIDTH и SNAKE_HEIGHT - константы, определяющие размер каждого сегмента змейки
    // FIELD_WIDTH и FIELD_HEIGHT - константы, определяющие размер игрового поля
    this->resize(SNAKE_WIDTH*FIELD_WIDTH, SNAKE_HEIGHT*FIELD_HEIGHT);

    // Устанавливаем заголовок окна "Змейка"
    this->setWindowTitle("Змейка");

    // Вызываем функцию _INIT_GAME() для инициализации игры
    _INIT_GAME();
}

void GameLogic::timerEvent(QTimerEvent * e)
{
    // Неиспользуемый параметр
    Q_UNUSED(e);

    // Проверяем, идет ли сейчас игра
    if(this->m_inGame){
        // Вызываем функцию _CHECK_APPLE() для проверки, съела ли змейка яблоко
        _CHECK_APPLE();
        // Вызываем функцию _SNAKE_MOVE() для перемещения змейки
        _SNAKE_MOVE();
        // Вызываем функцию _CHECK_FIELD_EXIT() для проверки, не вышла ли змейка за пределы игрового поля
        _CHECK_FIELD_EXIT();
    }

    // Перерисовываем игровое окно, чтобы обновить отображение
    this->repaint();
}
void GameLogic::keyPressEvent(QKeyEvent *event)
{
    // Получаем код нажатой клавиши
    int PRESSED_KEY = event->key();

    // Проверяем, какая клавиша была нажата, и меняем направление змейки соответствующим образом
    // Змейка не может поворачивать в противоположную сторону
    if(PRESSED_KEY == Qt::Key_Left && m_dir != Dirs::right){
        m_dir = Dirs::left;
    }
    else if(PRESSED_KEY == Qt::Key_Right && m_dir != Dirs::left){
        m_dir = Dirs::right;
    }
    else if(PRESSED_KEY == Qt::Key_Up && m_dir != Dirs::down){
        m_dir = Dirs::up;
    }
    else if(PRESSED_KEY == Qt::Key_Down && m_dir != Dirs::up){
        m_dir = Dirs::down;
    }
    // Также обрабатываем нажатие клавиш WASD для управления змейкой
    else if(PRESSED_KEY == Qt::Key_A && m_dir != Dirs::right){
        m_dir = Dirs::left;
    }
    else if(PRESSED_KEY == Qt::Key_D && m_dir != Dirs::left){
        m_dir = Dirs::right;
    }
    else if(PRESSED_KEY == Qt::Key_W && m_dir != Dirs::down){
        m_dir = Dirs::up;
    }
    else if(PRESSED_KEY == Qt::Key_S && m_dir != Dirs::up){
        m_dir = Dirs::down;
    }
}

void GameLogic::paintEvent(QPaintEvent *e)
{
    // Игнорируем параметр QPaintEvent, так как он не используется в этой функции
    Q_UNUSED(e);

    // Вызываем функцию, которая отвечает за отрисовку игровых элементов
    _DRAWING();
}

void GameLogic::_INIT_GAME()
{
    // Устанавливаем, что игра началась
    this->m_inGame = true;

    // Устанавливаем направление змейки вправо
    this->m_dir = right;

    // Создаем начальную змейку, состоящую из одного сегмента
    m_dots.resize(1);

    // Устанавливаем координаты начальной змейки
    for(int i = 0; i<m_dots.size(); i++){
        m_dots[i].setX(m_dots.size() - i - 1);
        m_dots[i].setY(0);
    }

    // Рисуем яблоко на игровом поле
    _DRAW_APPLE();

    // Устанавливаем начальную задержку между перемещениями змейки
    this->DELAY = 130;

    // Запускаем таймер, который будет вызывать обновление игры
    this->TIMER_ID = startTimer(this->DELAY);
}

void GameLogic::_DRAWING()
{
    // Создаем объект QPainter для рисования на виджете
    QPainter painter(this);

    // Проверяем, что игра началась
    if(this->m_inGame){
        // Устанавливаем кисть для рисования яблока
        painter.setBrush(this->m_colors[0]);
        // Рисуем яблоко на игровом поле
        painter.drawEllipse(m_apple.x() * SNAKE_WIDTH, m_apple.y() * SNAKE_HEIGHT, SNAKE_WIDTH, SNAKE_HEIGHT);

        // Получаем длину змейки
        size_t len = m_dots.size();
        // Проходим по всем сегментам змейки
        for(int i = 0; i<len;i++){
            // Если это голова змейки
            if(i==0){
                // Устанавливаем кисть для рисования головы змейки
                painter.setBrush(this->m_colors[1]);
                // Рисуем голову змейки
                painter.drawEllipse(m_dots[i].x() * SNAKE_WIDTH, m_dots[i].y() * SNAKE_HEIGHT, SNAKE_WIDTH, SNAKE_HEIGHT);
            }
            // Если это не голова змейки
            else{
                // Устанавливаем кисть для рисования тела змейки
                painter.setBrush(this->m_colors[2]);
                // Рисуем тело змейки
                painter.drawEllipse(m_dots[i].x() * SNAKE_WIDTH, m_dots[i].y() * SNAKE_HEIGHT, SNAKE_WIDTH, SNAKE_HEIGHT);
            }
        }
    }
    // Если игра закончилась
    else{
        // Вызываем функцию, которая обрабатывает окончание игры
        _GAME_OVER();
    }
}

void GameLogic::_DRAW_APPLE()
{
    // Получаем текущее время
    QTime time = QTime::currentTime();
    // Используем текущее время для инициализации генератора случайных чисел
    srand((uint) time.msec());

    // Генерируем случайные координаты яблока в пределах поля
    m_apple.setX(rand() % this->SNAKE_WIDTH);
    m_apple.setY(rand() % this->SNAKE_HEIGHT);
}

void GameLogic::_SNAKE_MOVE()
{
    // Перемещаем все сегменты змейки, кроме головы
    for(int i = m_dots.size() - 1; i > 0; i--){
        m_dots[i] = m_dots[i-1];
    }

    // Перемещаем голову змейки в зависимости от направления
    switch(this->m_dir){
    case left:
        m_dots[0].rx() -= 1;
        break;
    case right:
        m_dots[0].rx() += 1;
        break;
    case up:
        m_dots[0].ry() -= 1;
        break;
    case down:
        m_dots[0].ry() += 1;
        break;
    }
}

void GameLogic::_CHECK_FIELD_EXIT()
{
    // Получаем длину змейки
    int len = m_dots.size();

    // Если длина змейки больше 4, то проверяем на самопересечение
    if(len>4){
        for(int i = 1; i<len; i++){
            // Если координаты головы совпадают с координатами любого другого сегмента змейки
            if(m_dots[0]==m_dots[i]){
                // Значит змейка пересеклась сама с собой, игра окончена
                this->m_inGame = false;
            }
        }
    }

    // Проверяем выход змейки за границы поля
    if(m_dots[0].x() >= this->FIELD_WIDTH){
        // Если змейка вышла за правую границу, переносим ее на левую
        m_dots[0].setX(0);
    }
    else if(m_dots[0].x() < 0){
        // Если змейка вышла за левую границу, переносим ее на правую
        m_dots[0].setX(FIELD_WIDTH-1);
    }
    else if(m_dots[0].y() >= this->FIELD_HEIGHT){
        // Если змейка вышла за нижнюю границу, переносим ее на верхнюю
        m_dots[0].setY(0);
    }
    else if(m_dots[0].y() < 0){
        // Если змейка вышла за верхнюю границу, переносим ее на нижнюю
        m_dots[0].setY(FIELD_HEIGHT-1);
    }

    // Если игра окончена, останавливаем таймер
    if(!this->m_inGame){
        killTimer(this->TIMER_ID);
    }
}
void GameLogic::_GAME_OVER()
{
    // Создаем всплывающее окно с сообщением о поражении
    QMessageBox msgb;
    msgb.setText("Вы проиграли!");
    msgb.exec();

    // Инициализируем новую игру
    _INIT_GAME();
}

void GameLogic::_CHECK_APPLE()
{
    // Проверяем, совпадают ли координаты головы змейки с координатами яблока
    if(m_apple == m_dots[0]){
        // Если совпали, значит змейка съела яблоко

        // Добавляем новый сегмент к змейке
        m_dots.push_back(QPoint(0, 0));

        // Рисуем новое яблоко
        _DRAW_APPLE();

        // Увеличиваем скорость игры, уменьшая задержку между ходами
        this->DELAY -= 5;
    }
}
