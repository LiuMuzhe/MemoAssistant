#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Pages/p_manage.h"
#include "Pages/p_timeline.h"
#include "Pages/p_report.h"
#include "include/ElaWindow.h"
#include "database.h"
#include "Pages/p_home.h"
#include "QVBoxLayout"
#include "ElaDockWidget.h"
#include "userChoiceDialog.h"
#include <QMessageBox>

// 前向声明
class LoginDialog;

class MainWindow : public ElaWindow
{
    Q_OBJECT
private:
    // 数据相关
    Database *db{nullptr};
    QSqlDatabase accountDB;
    bool hasLoggedIn = false;
    User *usr{nullptr};
    QVector<Task> tasks;

    //界面相关
    P_Home *pHome{nullptr};
    P_Manage *pManage{nullptr};
    P_Timeline *pTimeline{nullptr};
    P_Report *pReport{nullptr};

    //Docker
    ElaDockWidget *rDocker{nullptr};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initWindow();
    void initContent();
    void initDB(QString dbName = "default");
    bool initAccountDB(QSqlError& mess);
    bool Login();
    void Logout();
    void updateUserInfoCard();
    void updateDocker();
    bool isLoggedIn() const { return hasLoggedIn; }
    User* getCurrentUser() const { return usr; }
    Database* getDatabase() const { return db; }
    QString getCurrentDatabaseName() const {
        return (hasLoggedIn && usr) ? usr->dbName : "default";
    }

private slots:
    // 用户信息卡片点击处理
    void handleUserInfoCardClick();

    // 退出登录确认
    void confirmLogout();

    // 执行退出登录
    void performLogout();

    void databaseChangedSlot();

private:
    // 登录相关方法
    void showLoginDialog();
    void handleLoginAttempt(const QString& name, const QString& pwd, LoginDialog* ld);
    void showUserChoiceDialog(const QString& name, const QString& pwd);
    void createNewUserWithCredentials(const QString& name, const QString& pwd);

    // 数据库相关方法
    bool createNewUser(const QString& name, const QString& pwd, QSqlQuery& query);
    bool createUserDatabase(const QString& dbName);

    // 用户菜单相关方法
    void showUserMenu();

    // 清理用户数据
    void clearUserData();

    // 重置界面到默认状态
    void resetToDefaultState();
};

#endif // MAINWINDOW_H
