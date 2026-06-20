#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QListWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initGraphData();
    setWindowTitle("항공권 조회 프로그램");
    setFixedSize(1200, 700);
    // 노선 데이터를 미리 준비하고, 화면 크기가 변하여 레이아웃이 깨지는 것을 방지하기 위해 그래프 데이터를 먼저 메모리에 불러온 후 창의 제목을 지정하고 setFixedSize 함수로 창 크기를 고정하여 화면의 전체적인 형태를 잡도록 하였다.

    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->setAlignment(Qt::AlignCenter);
    // 전체 화면을 크게 왼쪽에 시각적 노선도와 오른쪽에 상세 정보 패널로 분할하여 직관적인 조작이 가능하도록 구성하기 위해 중앙 위젯을 생성하고 수평 정렬 레이아웃을 적용하여 이후에 추가될 좌우 레이아웃이 나란히 배치되도록 하였다.

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addSpacing(70);

    QString imagePath = ":/map.png";
    QPixmap pixmap(imagePath);
    QLabel* imageLabel = new QLabel;

    if (pixmap.isNull()) {
        imageLabel->setText("<h3 style='color:red'>지도 이미지 로드 실패!</h3>");
    } else {
        imageLabel->setFixedSize(800, 500);
        imageLabel->setPixmap(pixmap.scaled(800, 500, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    leftLayout->addWidget(imageLabel);
    // 바탕이 되는 세계 지도 이미지를 화면 좌측에 배치하기 위해 준비된 지도 이미지 파일을 QPixmap으로 불러온 뒤 QLabel 위젯에 씌우고 크기를 조정하여 좌측 레이아웃에 추가하였다.

    QPushButton* btnGMP = new QPushButton("ICN", imageLabel);
    btnGMP->setGeometry(330, 120, 40, 30);

    QPushButton* btnCJU = new QPushButton("CJU", imageLabel);
    btnCJU->setGeometry(325, 140, 40, 30);

    QPushButton* btnNRT = new QPushButton("NRT", imageLabel);
    btnNRT->setGeometry(360, 125, 40, 30);

    QPushButton* btnHKG = new QPushButton("HKG", imageLabel);
    btnHKG->setGeometry(305, 170, 40, 30);

    QPushButton* btnLHR = new QPushButton("LHR", imageLabel);
    btnLHR->setGeometry(90, 70, 40, 30);

    QPushButton* btnLAX = new QPushButton("LAX", imageLabel);
    btnLAX->setGeometry(580, 130, 40, 30);

    QPushButton* btnJFK = new QPushButton("JFK", imageLabel);
    btnJFK->setGeometry(650, 105, 40, 30);
    // 직관적으로 공항을 선택할 수 있도록 실제 지리적 위치에 해당하는 곳에 공항 버튼을 고정시키기 위해 지도 이미지를 기준 객체로 삼고 setGeometry를 이용해 지도 상의 절대 좌표를 직접 지정하여 버튼을 지도 위에 겹쳐 배치하였다.

    QVBoxLayout* rightLayout = new QVBoxLayout();

    QLabel* rightTitle = new QLabel("<h2>공항을 클릭하세요</h2><p>좌측 노선도에서 공항(버튼)을 클릭하세요.</p>");
    rightTitle->setFixedHeight(70);
    rightTitle->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    QListWidget* departList = new QListWidget();
    departList->setStyleSheet("background-color: #2b2b2b; color: white; padding: 10px; border-radius: 5px; font-size: 14px;");
    departList->setFixedHeight(245);

    QListWidget* arriveList = new QListWidget();
    arriveList->setStyleSheet("background-color: #2b2b2b; color: white; padding: 10px; border-radius: 5px; font-size: 14px;");
    arriveList->setFixedHeight(245);
    // 항공편 목록의 가독성을 높이기 위해 QListWidget을 생성하고 setStyleSheet를 통해 다크 모드 기반의 배경색, 글씨색, 모서리 둥글기 등의 시각적 디자인 요소를 적용하였다.

    rightLayout->addWidget(rightTitle);
    rightLayout->addWidget(departList);
    rightLayout->addWidget(arriveList);

    mainLayout->addLayout(leftLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(rightLayout);
    // 우측 화면에 안내 문구와 두 개의 리스트를 수직으로 정렬하고 최종적으로 좌우 화면이 하나로 합쳐지게 하기 위해 수직 정렬 레이아웃에 우측 위젯들을 쌓아 올린 뒤 메인 수평 레이아웃에 좌측과 우측 레이아웃을 차례대로 추가했다.

    auto showFlightInfo = [this, departList, arriveList, rightTitle](QString airportCode) {
        departList->clear();
        arriveList->clear();

        QString airportName = airportCode;
        if (airportCode == "ICN") airportName = "인천";
        else if (airportCode == "CJU") airportName = "제주";
        else if (airportCode == "NRT") airportName = "도쿄(나리타)";
        else if (airportCode == "HKG") airportName = "홍콩";
        else if (airportCode == "LHR") airportName = "런던";
        else if (airportCode == "LAX") airportName = "LA";
        else if (airportCode == "JFK") airportName = "뉴욕";

        rightTitle->setText(QString("<h2>%1 (%2)</h2><p>아래 항공편을 클릭하면 예매됩니다.</p>").arg(airportName, airportCode));
        // 특정 공항 버튼을 눌렀을 때 이전 검색 결과를 지우고 해당 공항에 맞는 한글 이름으로 안내 문구를 갱신하기 위해 내부 동작 블록을 만들어 리스트를 비운 뒤 조건문을 통해 공항 코드에 맞는 이름을 제목 라벨에 설정하도록 하였다.

        int depCount = flightGraph[airportCode].size();
        departList->addItem(QString("▶ 출발 항공편 (%1편)").arg(depCount));
        departList->item(0)->setFlags(Qt::NoItemFlags);
        // 선택한 공항에서 출발하는 노선이 몇 개인지 알려주고 첫 번째 줄을 클릭할 수 없는 제목 줄로 띄워 구분하기 위해 인접 리스트의 특성을 활용해 Key 값으로 연결된 데이터 개수를 구하고, 제목 아이템의 속성을 수정하여 클릭 조작을 막았다.

        for (const Flight& f : flightGraph[airportCode]) {
            QString timeStr = QString::number(f.duration / 60) + "시간 " + QString::number(f.duration % 60) + "분";
            QString priceStr = "₩" + QString("%L1").arg(f.price);

            departList->addItem("[" + airportCode + " -> " + f.destination + "] ‧ " + priceStr + " ‧ " + timeStr);
            // 정보를 파악하기 쉽도록 비행시간을 시간/분으로 변환하고, 가격에 천 단위 구분 기호를 추가했다.

        }

        int arrCount = 0;
        for (const QString& startAirport : flightGraph.keys()) {
            for (const Flight& f : flightGraph[startAirport]) {
                if (f.destination == airportCode) arrCount++;
            }
        }

        arriveList->addItem(QString("▶ 도착 항공편 (%1편)").arg(arrCount));
        arriveList->item(0)->setFlags(Qt::NoItemFlags);
        // 특정 공항으로 도착하는 모든 노선을 그래프 전체에서 찾아내어 총 몇 편인지 계산하고 도착 리스트의 제목 줄을 띄우기 위해 전체 그래프 노드의 출발지를 순회하며 목적지가 현재 선택된 공항과 일치하는 횟수를 세어 제목으로 추가하도록 하였다.

        for (const QString& startAirport : flightGraph.keys()) {
            for (const Flight& f : flightGraph[startAirport]) {
                if (f.destination == airportCode) {
                    QString timeStr = QString::number(f.duration / 60) + "시간 " + QString::number(f.duration % 60) + "분";
                    QString priceStr = "₩" + QString("%L1").arg(f.price);

                    arriveList->addItem("[" + startAirport + " -> " + airportCode + "] ‧ " + priceStr + " ‧ " + timeStr);
                }
            }
        }
    };
    // 찾아낸 도착 항공편들의 상세 정보의 가독성을 높이기 위해 그래프를 다시 순회하면서 목적지가 일치하는 노선만 걸러낸 뒤, 시간과 가격 데이터를 문자열로 변환하여 도착 리스트에 차례대로 삽입하도록 하였다.

    connect(btnGMP, &QPushButton::clicked, this, [=]() { showFlightInfo("ICN"); });
    connect(btnCJU, &QPushButton::clicked, this, [=]() { showFlightInfo("CJU"); });
    connect(btnNRT, &QPushButton::clicked, this, [=]() { showFlightInfo("NRT"); });
    connect(btnHKG, &QPushButton::clicked, this, [=]() { showFlightInfo("HKG"); });
    connect(btnLHR, &QPushButton::clicked, this, [=]() { showFlightInfo("LHR"); });
    connect(btnLAX, &QPushButton::clicked, this, [=]() { showFlightInfo("LAX"); });
    connect(btnJFK, &QPushButton::clicked, this, [=]() { showFlightInfo("JFK"); });
    // 화면에 띄워둔 버튼들이 실제로 눌렸을 때 해당 공항에 맞는 항공편 출력 기능이 즉각적으로 작동하도록 이어주기 위해 connect 함수를 사용하여 버튼의 클릭 조작을 감지하면 알맞은 공항 코드를 정보 갱신 블록에 전달하도록 연결하였다.

    auto bookFlight = [this](QListWidgetItem* item) {
        QMessageBox::information(this, "예매 완료", "예매가 완료되었습니다.\n\n" + item->text());
    };
    // 리스트에서 특정 항공편을 클릭했을 때 알림창을 띄워 사용자에게 예매가 정상적으로 완료되었음을 피드백하기 위해 클릭된 리스트의 텍스트 정보를 받아와서 화면 중앙에 메시지 박스를 띄워 안내 문구와 함께 출력하는 내부 동작 블록을 정의하였다.

    connect(departList, &QListWidget::itemClicked, this, bookFlight);
    connect(arriveList, &QListWidget::itemClicked, this, bookFlight);
    // 출발 및 도착 리스트 위젯에서 실제로 항목을 클릭하는 조작이 발생했을 때 예매 완료 알림창이 뜨도록 만들기 위해 connect 함수로 두 리스트 위젯의 항목 클릭 조작을 감지하여 앞서 만든 예매 피드백 블록과 연결하였다.
}

MainWindow::~MainWindow()
{
    delete ui;
}
// 프로그램 창이 닫히고 종료될 때 더 이상 사용하지 않는 화면 구성 요소들이 메모리를 차지하지 않도록 정리하기 위해 소멸자 내부에서 ui 포인터를 delete로 삭제하여 윈도우 객체 내부에 동적으로 할당되었던 메모리를 안전하게 해제하도록 하였다.

void MainWindow::initGraphData() {

    flightGraph.clear();

    flightGraph["ICN"].push_back({"CJU", 60, 85000});
    flightGraph["CJU"].push_back({"ICN", 60, 85000});

    flightGraph["ICN"].push_back({"NRT", 120, 250000});
    flightGraph["NRT"].push_back({"ICN", 120, 250000});

    flightGraph["HKG"].push_back({"NRT", 240, 400000});
    flightGraph["NRT"].push_back({"HKG", 240, 400000});

    flightGraph["ICN"].push_back({"LAX", 660, 1200000});
    flightGraph["LAX"].push_back({"ICN", 660, 1200000});

    flightGraph["ICN"].push_back({"JFK", 840, 1500000});
    flightGraph["JFK"].push_back({"ICN", 840, 1500000});

    flightGraph["ICN"].push_back({"LHR", 840, 1400000});
    flightGraph["LHR"].push_back({"ICN", 840, 1400000});

    flightGraph["JFK"].push_back({"LHR", 420, 800000});
    flightGraph["LHR"].push_back({"JFK", 420, 800000});

    flightGraph["LAX"].push_back({"JFK", 330, 600000});
    flightGraph["JFK"].push_back({"LAX", 330, 600000});

    flightGraph["LAX"].push_back({"LHR", 630, 1100000});
    flightGraph["LHR"].push_back({"LAX", 630, 1100000});

    flightGraph["NRT"].push_back({"LAX", 600, 1000000});
    flightGraph["LAX"].push_back({"NRT", 600, 1000000});

    flightGraph["NRT"].push_back({"JFK", 840, 1450000});
    flightGraph["JFK"].push_back({"NRT", 840, 1450000});

    flightGraph["NRT"].push_back({"LHR", 870, 1500000});
    flightGraph["LHR"].push_back({"NRT", 870, 1500000});

    flightGraph["HKG"].push_back({"LHR", 840, 1300000});
    flightGraph["LHR"].push_back({"HKG", 840, 1300000});

    flightGraph["HKG"].push_back({"LAX", 900, 1400000});
    flightGraph["LAX"].push_back({"HKG", 900, 1400000});

    flightGraph["HKG"].push_back({"JFK", 960, 1600000});
    flightGraph["JFK"].push_back({"HKG", 960, 1600000});
}
// 예매 시스템의 뼈대가 되는 전 세계 주요 항공 노선도를 초기에 세팅하여 프로그램 동작 시 활용하기 위해 QMap 자료구조를 초기화한 후, 출발지를 지정하고 목적지,비행시간,가격을 구조체로 묶어 순차적으로 추가하였으며, 왕복 통행이 가능하도록 두 공항 간의 데이터를 교차로 입력하였다.