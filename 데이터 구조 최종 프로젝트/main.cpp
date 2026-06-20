#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 운영체제로부터 실행 명령을 받아 GUI 프로그램의 바탕 환경을 초기화하고, 메인 화면을 띄운 뒤 사용자의 조작을 대기하도록 Qt GUI 프로그램의 핵심 관리자인 QApplication 객체를 생성하여 조작을 감지할 수 있는 시스템 환경을 준비한다.

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "flight_booking_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    // 프로그램이 실행되는 컴퓨터의 운영체제 언어 설정에 맞춰 자동으로 프로그램의 텍스트 언어를 적용하기 위해 시스템의 언어 목록을 불러온 뒤 반복문을 통해 프로젝트 내에 일치하는 번역 파일이 존재하는지 확인하고 적용한다.

    MainWindow w;
    w.show();
    // 설계한 항공권 예매 시스템의 메인 화면을 실제로 생성하고 시각화하기 위해 MainWindow 클래스를 기반으로 윈도우 객체w를 메모리에 생성한 뒤 show() 함수를 호출하여 화면에 띄운다.

    return QApplication::exec();
    // 코드가 한 번 다 실행되어도 사용자가 종료 버튼을 누를 때까지 켜진 상태를 계속 유지하도록 만들기 위해 exec() 함수를 호출하여 프로그램 작동을 무한 대기 상태로 만든다.
}
