#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parcer.h"
#include <vector>
#include <iostream>
#include "writertofile.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    start_ball.is = false;
    finish_ball.is = false;
    _number_of_click = 0;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
*  @brief
*  Главный метод парсера
*/

void MainWindow::paintEvent(QPaintEvent *event)
{
    int shift = 3;
    Q_UNUSED(event);
    QPainter painter(this);
    QColor color;
    color.setNamedColor(ui->color_lines_comboBox->currentText());
    painter.setPen(QPen(color, ui->widht_line_spin->value(), Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(color, Qt::SolidPattern));
    if (ui->tabWidget->currentIndex() == 0) {

        float step_x = 500.0/maze_scheme.size_col, step_y = 500.0/ maze_scheme.size_rows;
        float start_pos_x = 0 + shift, start_pos_y = 0 + shift;
        if(!maze_scheme.first.empty() && !maze_scheme.second.empty()) {
        // Отрисовщик
        auto it_first = maze_scheme.first.begin();
        int count = 0;
        for (; it_first != maze_scheme.first.end(); it_first++) {
            start_pos_x += step_x;
            if (*it_first) {
                 painter.drawLine(start_pos_x, start_pos_y, start_pos_x, start_pos_y+step_y);
            }
            count++;
            if (count == maze_scheme.size_col) {
                count = 0;
                start_pos_y += step_y;
                start_pos_x = 0 + shift;
            }
        }

            painter.drawLine(0 + shift, 0 + shift, 0 + shift, 500 + shift);
            painter.drawLine(0 + shift, 0 + shift, 500 + shift, 0 + shift);
            start_pos_x = 0 + shift, start_pos_y = step_y + shift;
            auto it_second = maze_scheme.second.begin();
            count = 0;

            for (; it_second != maze_scheme.second.end(); it_second++) {
                if (*it_second) {
                       painter.drawLine(QPointF(start_pos_x, start_pos_y), QPointF( start_pos_x + step_x, start_pos_y));
                    // painter.drawLine(start_pos_x, start_pos_y, start_pos_x + step_x, start_pos_y);

                }
                start_pos_x += step_x;
                count++;
                if (count == maze_scheme.size_col) {
                   start_pos_x = 0 + shift;
                   start_pos_y += step_y;
                   count = 0;
                }
            }

            // Рисуем круги
            
            if(!maze_scheme.line_way.empty()) {
                // Отрисовываем линии
                color.setNamedColor("red");
                painter.setPen(QPen(color, ui->widht_line_spin->value(), Qt::SolidLine, Qt::FlatCap));

                auto it = array_lines.begin();
                for (; it != array_lines.end(); it++) {
                    painter.drawLine(QPointF(it->x_start, it->y_start), QPointF(it->x_finish, it->y_finish));
                }
            }

            if (start_ball.is) {
                QImage image;
                image.load("images/mouse.png");
                 QColor color;
                 color.setNamedColor("green");
                draw_ball( image,
                          start_ball, &painter, color);
               }
            if (finish_ball.is) {
                QImage image;
                image.load("images/cheese.png");
                QColor color;
                color.setNamedColor("red");
                draw_ball(image,
                          finish_ball, &painter, color);
            }

        }
        } else {
         if(!cave_scheme.first.empty()) {
            int start_pos_x = 0, start_pos_y = 0;
            int step_x = 500/cave_scheme.size_col, step_y = 500 / cave_scheme.size_rows;
            auto it_first = cave_scheme.first.begin();
            int count = 0;
            for (; it_first != cave_scheme.first.end(); it_first++) {
                if (*it_first) {
                     painter.setBrush(QBrush(color, Qt::SolidPattern));
                     painter.drawRect(QRect(start_pos_x, start_pos_y, step_x, step_y));
                }
                start_pos_x += step_x;
                count++;
                if (count == cave_scheme.size_col) {
                   start_pos_x = 0;
                   start_pos_y += step_y;
                   count = 0;
                }
            }
        }
    }

}

void MainWindow::on_save_maze_button_clicked()
{
     WriterToFile write;
     QString path;
     QFileDialog dialog;
     if (maze_scheme.first.empty()) {
        QMessageBox::critical(this, "Лабирита нет", "Сначала откройте/сгенерируйте лабиринт");
        return;
    }
     path = dialog.getSaveFileName(this);
     write.start_write(maze_scheme, path.toStdString());
     this->start_ball.is = false;
     this->finish_ball.is = false;

}

void MainWindow::on_open_maze_btn_clicked()
{
    Parcer parcer;
    QFileDialog dialog;
    QString path;
    path = dialog.getOpenFileName(this);
    clear(&maze_scheme);
    if (parcer.start_parcer(maze_scheme, path.toStdString()) != 0)
        QMessageBox::critical(this, "Ошибка Парсинга", "Ошибка Парсинга");

    repaint();
}


void MainWindow::on_open_cave_btn_clicked()
{
    Parcer parcer;
    QFileDialog dialog;
    QString path;
    path = dialog.getOpenFileName(this);
    cave_scheme.first.clear();
    cave_scheme.second.clear();
    if (parcer.start_parcer(cave_scheme, path.toStdString()) != 0)
        QMessageBox::critical(this, "Ошибка Парсинга", "Ошибка Парсинга");

}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    ui->tabWidget->setCurrentIndex(index);
    repaint();
}


void MainWindow::on_generate_maze_btn_clicked()
{
    _number_of_click = 0;
    Eller generator;
    generator.start_create_maze_eller(&maze_scheme, ui->rows_spin->value(), ui->cols_spin->value());
    start_ball.is = false;
    finish_ball.is = false;
    maze_scheme.line_way.clear();
    repaint();
}


void MainWindow::on_widht_line_spin_valueChanged(int arg1)
{
    arg1 = 0; arg1++;
    repaint();
}


void MainWindow::on_color_lines_comboBox_currentTextChanged(const QString &arg1)
{   
    repaint();
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if( !(event->pos().x() > 3 && event->pos().x() < 500 &&
            event->pos().y() > 3 && event->pos().y() < 500))
        return;

  
    if (!maze_scheme.first.empty() && !maze_scheme.second.empty()){
       // Какой это клик по счету?
       // Если клик первый или второй считаем и создаем соответствующие объекты шарика
       // Если клик тритий обнуляем объекты.
       // в любом случае клик
       int row = 0, col = 0,
           radius_row = 0, radius_col = 0,
           center_row = 0, center_cols = 0;
       if (_number_of_click != 2) {
           row = (event->pos().y() / 500.0) * 
           maze_scheme.size_rows;
           col = (event->pos().x() / 500.0) 
           * maze_scheme.size_col;
           radius_row = 500/maze_scheme.size_rows;
           radius_col =  500/maze_scheme.size_col;
           center_row =  500.0/maze_scheme.size_rows * (row) + (radius_row/2);
           center_cols =  500.0/maze_scheme.size_col * (col) + (radius_col/2);
       }
        
       switch(_number_of_click) {
        case 0:
           start_ball.is = true;
           start_ball.radius_x = radius_col;
           start_ball.radius_y = radius_row;
           start_ball.x_pos = center_cols;
           start_ball.y_pos = center_row;
           start_ball.row = row;
           start_ball.col = col;
           _number_of_click++;
           break;

        case 1:
           finish_ball.is = true;
           finish_ball.radius_x = radius_col;
           finish_ball.radius_y = radius_row;
           finish_ball.x_pos = center_cols;
           finish_ball.y_pos = center_row;
           finish_ball.row = row;
           finish_ball.col = col;
           _number_of_click++;
           break;
        case 2:
           start_ball.is = false;
           finish_ball.is = false;
           maze_scheme.line_way.clear();
           _number_of_click = 0;
           break;
       }
    }
    repaint();
}


void MainWindow::on_find_way_btn_clicked()
{
    if (start_ball.is && finish_ball.is) {
        MikkiMouse finder;
        finder.start_searching(&maze_scheme, start_ball, finish_ball);
        finder.point_array_creation(&maze_scheme, &array_lines);
    } else {
        QMessageBox::critical(this, "Error", "Сначала введите начальную и конечную точку");
    }
    repaint();
}


void MainWindow::on_clear_maze_clicked()
{
    start_ball.is = false;
    finish_ball.is = false;
    clear(&maze_scheme);
    _number_of_click = 0;
    repaint();
}

void MainWindow::draw_ball(QImage image, baloon ball, QPainter * painter,  QColor color) {

    float radius = 0;
    ball.radius_x <= ball.radius_y ?
                  radius = ball.radius_x : radius = start_ball.radius_y;
    if (image.isNull()) {
        painter->setBrush(QBrush(color, Qt::SolidPattern));
        painter->drawRect(ball.x_pos + 3 - radius/2*0.8,
                          ball.y_pos + 3 - radius/2*0.8,
                          radius*0.8 ,
                          radius*0.8);
    }

    painter->drawImage(QRect(ball.x_pos + 3 - radius/2*0.8,
                             ball.y_pos + 3 - radius/2*0.8,
                             radius*0.8 ,
                             radius*0.8 ), image);

}

void MainWindow::init_cave() {
     clear(&cave_scheme);
    cave_scheme.size_col = ui->cols_cave_spin->value();
    cave_scheme.size_rows = ui->rows_cave_spin->value();
    initCave init;
    init.start_init(&cave_scheme, ui->cave_percent_spinBox->value());
}

void MainWindow::sleep(qint64 msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

void MainWindow::on_generate_cave_btn_clicked()
{
    if (cave_scheme.first.empty()) {
        init_cave();
    }
    genCave generator;
    if(ui->auto_radioButton->isChecked()) {
        for (int i = 0; i < ui->steps_spinBox_2->value(); i++) {
            sleep(ui->time_spinBox->value());
            generator.start_gen(cave_scheme, 1,  ui->spinBirth->value(), ui->spinDeath->value());
            repaint();
        }

    } else if (ui->manual_radioButton_2->isChecked()) {
        generator.start_gen(cave_scheme, 1,  ui->spinBirth->value(), ui->spinDeath->value());
    }
    repaint();
}


void MainWindow::on_init_cave_btn_clicked()
{
    init_cave();
    repaint();
}


void MainWindow::on_radioButton_2_clicked(bool checked)
{
    ui->auto_radioButton->setChecked(0);
}


void MainWindow::on_clear_cave_btn_clicked()
{
    clear(&cave_scheme);
    repaint();
}

void MainWindow::clear(model * scheme) {
    scheme->first.clear();
    scheme->second.clear();
    scheme->line_way.clear();
    scheme->size_col = 0;
    scheme->size_rows = 0;
    start_ball.is = false;
    finish_ball.is = false;
    this->_number_of_click = 0;
}

void MainWindow::on_action_triggered()
{
    exit(0);
}

