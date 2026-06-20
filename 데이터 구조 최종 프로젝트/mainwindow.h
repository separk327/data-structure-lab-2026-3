#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QVector>
#include <QMap>
// GUI 화면 구성 및 데이터 처리에 필요한 Qt 프레임워크의 기본 도구들을 불러온다.

struct Flight {
    QString destination;
    int duration;
    int price;
};
// 비행기 노선이 가지는 정보 중 예매 시스템에 필요한 핵심 데이터만 선별하여 관리하기 위해 목적지, 비행시간, 가격이라는 3가지 핵심 변수를 'Flight'라는 하나의 구조체로 묶어 추상화하였다.

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// 프로그램의 전체 화면을 구성하고, 사용자의 화면 조작에 즉각적으로 반응하는 중앙 제어 객체를 만들기 위하여 Qt의 기본 창 도구인 QMainWindow를 상속받아 윈도우의 시각적인 뼈대를 형성하고, 내부 기능을 확장했다.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    //프로그램 동작에 필요한 핵심 데이터와 하위 요소들을 외부에서 함부로 접근하지 못하게 보호하고 통제하기 위하여 UI 요소와 그래프 데이터 구조를 private 멤버 변수로 선언하여 내부에서만 관리하도록 하였다.
    Ui::MainWindow *ui;

    QMap<QString, QVector<Flight>> flightGraph;
    // 무의미한 빈칸이 생기는 2차원 배열을 피하고 메모리 효율을 높이기 위해 출발지 공항 이름을 Key로 삼고, 해당 공항에서 출발하는 여러 비행편들의 집합을 Value로 가지는 QMap을 사용하여 인접 리스트 형태로 설계했다.

    void initGraphData();
    // 초기 그래프 데이터를 입력하는 코드가 길어 생성자 내부가 복잡해지는 것을 방지하기 위해 데이터를 세팅하는 역할만 전담하는 별도의 내부 함수를 만들어 코드를 분리하였다.
};
#endif // MAINWINDOW_H
