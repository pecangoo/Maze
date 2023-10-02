#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <models.h>
#include <eller.h>
#include <QMouseEvent>
#include <mikkimouse.h>
#include <QMessageBox>
#include "init_cave.h"
#include "gencave.h"
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    model maze_scheme;
    model cave_scheme;

protected:
    /* Определяем виртуальный метод родительского класса
     * для отрисовки содержимого виджета
     * */
    void paintEvent(QPaintEvent *event);

private slots:
    void on_save_maze_button_clicked();
    void on_open_maze_btn_clicked();
    void on_open_cave_btn_clicked();
    void on_tabWidget_tabBarClicked(int index);
    void on_generate_maze_btn_clicked();
    void on_widht_line_spin_valueChanged(int arg1);
    void on_color_lines_comboBox_currentTextChanged(const QString &arg1);
    void mousePressEvent(QMouseEvent* event);


    void on_find_way_btn_clicked();

    void on_clear_maze_clicked();

    void on_generate_cave_btn_clicked();

    void on_init_cave_btn_clicked();

    void on_radioButton_2_clicked(bool checked);

    void on_clear_cave_btn_clicked();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    baloon start_ball, finish_ball;
    int _number_of_click;
    std::vector<line_points> array_lines;
    void draw_ball(QImage image, baloon ball, QPainter * painter,  QColor color);
    void init_cave();
    void sleep(qint64 msec);
    void clear(model * scheme);
};
#endif // MAINWINDOW_H
