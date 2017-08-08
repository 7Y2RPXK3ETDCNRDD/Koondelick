#ifndef TASKADDDIALOG_H
#define TASKADDDIALOG_H

#include <QDialog>
#include "models/task.h"
class IconManager;
class QTimeEdit;

namespace Ui {
class TaskAddDialog;
}

class TaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskDialog(QDate current_date, QWidget *parent = 0);
    ~TaskDialog();

signals:
    void changed();

private:
    Ui::TaskAddDialog *ui;
    IconManager* icon_mng;
    QDate current_date;
    Task current_task;

    void initConnects();
    void drawTasks();
    QWidget* genTask(Task task);

    void addDayTask(int task_id, QTimeEdit* start_time, QTimeEdit* duration);
    void addTask(QString icon_path, QString name, int group_id);
};

#endif // TASKADDDIALOG_H
