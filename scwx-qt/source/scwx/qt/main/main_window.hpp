#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

namespace scwx
{
namespace qt
{
namespace main
{

class MainWindow : public QMainWindow
{
   Q_OBJECT

   friend class MainWindowImpl;

public:
   MainWindow(QWidget* parent = nullptr);
   ~MainWindow();

   void showEvent(QShowEvent* event) override;

private slots:
   void on_actionOpen_triggered();
   void on_actionExit_triggered();
   void on_resourceTreeCollapseAllButton_clicked();
   void on_resourceTreeExpandAllButton_clicked();

private:
   std::unique_ptr<MainWindowImpl> p;
   Ui::MainWindow*                 ui;
};

} // namespace main
} // namespace qt
} // namespace scwx
