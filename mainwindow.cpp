/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Body implementation of the mainwindow for the tactics program.
                Handles displaying the UI elements for each individual tactic
                like information or push buttons as well as the UI elements
                for the free-play mode.
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabelcircle.h"
#include "model.h"
#include <QPixmap>
#include <QImage>
#include <QPushButton>
#include <QPoint>
using std::vector;

MainWindow::MainWindow(Model& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), quizWindow(model)
{
    ui->setupUi(this);
    ui->freePlayBackground->setVisible(false);
    currentlyClickedSoldierID = -1; // this is a place holder to show in freeplay, that no current soldier is selected.

    connect(&model,
            &Model::showCompletedTacticStatus,
            this,
            &MainWindow::receiveCompletedTacticStatus);
    connect(this,
            &MainWindow::setNoActiveTool,
            &model,
            &Model::receiveSetNoActiveTool);
    connect(&model,
            &Model::toggleToolStatus,
            this,
            &MainWindow::receiveToggleToolStatus);
    connect(&model,
            &Model::sendTrajectoryPoint,
            this,
            &MainWindow::receiveTrajectoryPoint);
    connect(&model,
            &Model::toggleTrajectoryTool,
            this,
            &MainWindow::receiveToggleTrajectoryTool);
    connect(&model,
            &Model::togglePlaceEnemyTool,
            this,
            &MainWindow::receiveTogglePlaceEnemyTool);
    connect(&model,
            &Model::togglePlaceAllyTool,
            this,
            &MainWindow::receiveTogglePlaceAllyTool);
    connect(ui->placeAllyButton,
            &QPushButton::clicked,
            &model,
            &Model::setActiveToolPlaceAlly);
    connect(ui->placeEnemyButton,
            &QPushButton::clicked,
            &model,
            &Model::setActiveToolPlaceEnemy);
    connect(ui->setTrajectoryPoint,
            &QPushButton::clicked,
            &model,
            &Model::setActiveToolTrajectoryPoint);
    connect(this,
            &MainWindow::sendAnimationMouseCoordinates,
            &model,
            &Model::receiveMouseCoordinates);
    connect(ui->freeplay,
            &QPushButton::clicked,
            &model,
            &Model::enableFreePlay);
    connect(&model,
            &Model::startFreePlayMode,
            this,
            &MainWindow::receiveStartFreePlayMode);
    connect(ui->playButton,
            &QPushButton::clicked,
            this,
            &MainWindow::toggleTacticButtons);

    connect(this,
            &MainWindow::sendStartAnimation,
            &model,
            &Model::startAnimation);
    connect(&model.animations,
            &AnimationModel::moveLabel,
            this,
            &MainWindow::moveSoldierLabel);
    connect(&model,
            &Model::makeASoldierLabel,
            this,
            &MainWindow::makeNewQLabel);
    connect(&model,
            &Model::setBackground,
            this,
            &MainWindow::changeBackgroundLabel);

    connect(this,
            &MainWindow::quizSelection,
            &model,
            &Model::changeQuizSelection);

    uniqueAccesses[0][0] = true;
    currentTacticID = 0;
    isFreeSimStepPlaying = false;

    connect(ui->descriptionButton,
            &QPushButton::clicked,
            &model,
            &Model::getDescription);
    connect(ui->historyButton,
            &QPushButton::clicked,
            &model,
            &Model::getHistory);
    connect(ui->funFactsButton,
            &QPushButton::clicked,
            &model,
            &Model::getFunFacts);
    connect(&model,
            &Model::updateContent,
            this,
            &MainWindow::receiveUpdatedContent);
    connect(this,
            &MainWindow::initializeContentBox,
            &model,
            &Model::getDescription);
    connect(ui->quizButton,
            &QPushButton::clicked,
            this,
            &MainWindow::showQuizWindow);
    connect(&model.animations,
            &AnimationModel::clearLabels,
            this,
            &MainWindow::clearQLabels);
    connect(&model,
            &Model::hidePlayButton,
            ui->playButton,
            &QPushButton::hide);
    connect(&model.animations,
            &AnimationModel::showPlayButton,
            ui->playButton,
            &QPushButton::show);
    connect(&model.animations,
            &AnimationModel::showPlayButton,
            this,
            &MainWindow::toggleTacticButtons);
    connect(this,
            &MainWindow::onLoad,
            &model,
            &Model::prepopulateInitialTactic);
    connect(&model,
            &Model::enableFreePlayButton,
            this,
            &MainWindow::receiveEnableFreePlayButton);
    connect(ui->freeSimPlayButton,
            &QPushButton::clicked,
            &model,
            &Model::simulateFreeSimStep);
    connect(ui->freeSimPlayButton,
            &QPushButton::clicked,
            this,
            &MainWindow::deselectAllTools);
    connect(ui->resetAnimationButton,
            &QPushButton::clicked,
            this,
            &MainWindow::resetFreeSim);
    connect(this,
            &MainWindow::sendResetFreeSim,
            &model,
            &Model::receiveResetFreeSim);
    connect(ui->endFreePlayButton,
            &QPushButton::clicked,
            this,
            &MainWindow::resetFreeSim);
    connect(this,
            &MainWindow::sendEndFreePlay,
            &model,
            &Model::endFreePlay);

    tacticButtons.push_back(ui->tactic1);
    tacticButtons.push_back(ui->tactic2);
    tacticButtons.push_back(ui->tactic3);
    tacticButtons.push_back(ui->tactic4);
    tacticButtons.push_back(ui->tactic5);
    tacticButtons.push_back(ui->tactic6);

    for(QPushButton* button : tacticButtons)
    {
        connect(button,
                &QPushButton::clicked,
                &model,
                &Model::changeTactic);
    }

    initializeContent();
    updateTheme("background-color: rgb(224,255,210);",
                "background-color: rgb(150,172,135);",
                "background-color: rgb(90,123,94);",
                "background-color: rgb(127, 131, 134);");
    ui->freeplay->setEnabled(false);

    emit onLoad();  // MUST BE LAST
}

void MainWindow::moveSoldierLabel(int soldierId, int x, int y)
{
    listOfSoldierLabels[soldierId]->move(x, y);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int mousePressX = event->pos().x();
    int mousePressY = event->pos().y();

    // Check if the mouse coordinates are within bounds.
    if(mousePressX >= 150 && mousePressY <= 342)
        emit sendAnimationMouseCoordinates(QPoint(mousePressX, mousePressY), currentlyClickedSoldierID);
}

void MainWindow::makeNewQLabel(QPoint pos, bool isEnemy, bool isFreePlayEnabled, int labelID)
{
    QLabel* label;
    ClickableLabelCircle* testLabel;
    //makes a different type of label that can be clicked for freePlay
    if(isFreePlayEnabled)
    {
        testLabel = new ClickableLabelCircle(50, labelID, this->centralWidget());
        testLabel->setText("");

        connect(testLabel,
                &ClickableLabelCircle::clicked,
                this,
                &MainWindow::getPlayableSoldierData);

        label = testLabel;
    }
    else
        label = new QLabel("", this->centralWidget());

    label->size() = QSize(50, 50);
    if(isEnemy)
       label->setPixmap(QPixmap(":/circle_enemy.png"));
    else
       label->setPixmap(QPixmap(":/circle_friend.png"));
    //assigns a position
    label->move(pos.x(), pos.y());
    listOfSoldierLabels.append(label);
    //display setup
    listOfSoldierLabels[listOfSoldierLabels.size()- 1]->show();
    listOfSoldierLabels[listOfSoldierLabels.size()- 1]->stackUnder(ui->tacticScrollArea);
}

void MainWindow::changeBackgroundLabel(QPixmap image)
{
    this->ui->backgroundLabel->setPixmap(image);
    this->ui->backgroundLabel->show();
}
void MainWindow::showQuizWindow()
{
    emit quizSelection();
    quizWindow.show();
}

void MainWindow::initializeContent()
{
    emit initializeContentBox();
}

void MainWindow::receiveUpdatedContent(QString content, QString category, int tacticID)
{
    //updates content appropiately on central UI
    ui->textBox->setText(content);

    if(currentTacticID != tacticID)
    {
        currentTacticID = tacticID;
        quizWindow.close();
        switch(currentTacticID)
        {
            case 0:
                updateTheme("background-color: rgb(224,255,210);",
                            "background-color: rgb(150,172,135);",
                            "background-color: rgb(90,123,94);",
                            "background-color: rgb(127, 131, 134);");
                break;
            case 1:
                updateTheme("background-color: rgb(224,255,210);",
                            "background-color: rgb(150,172,135);",
                            "background-color: rgb(90,123,94);",
                            "background-color: rgb(15,234,195);");
                break;
            case 2:
                updateTheme("background-color: rgb(240,227,129);",
                            "background-color: rgb(209,193,79);",
                            "background-color: rgb(132,141,156);",
                            "background-color: rgb(0,130,148);");
                break;
            case 3:
                updateTheme("background-color: rgb(255,255,255);",
                            "background-color: rgb(220,220,220);",
                            "background-color: rgb(192,192,192);",
                            "background-color: rgb(181,233,255);");
                break;
            case 4:
                updateTheme("background-color: rgb(255,170,128);",
                            "background-color: rgb(117,25,0);",
                            "background-color: rgb(90,80,80);",
                            "background-color: rgb(0,0,0);");
                break;
            case 5:
                updateTheme("background-color: rgb(255,255,191);",
                            "background-color: rgb(219,195,0);",
                            "background-color: rgb(68,74,80);",
                            "background-color: rgb(0,0,0);");
                break;
        }
    }

    if(category == "description")
    {
        ui->descriptionButton->setEnabled(false);
        ui->funFactsButton->setEnabled(true);
        ui->historyButton->setEnabled(true);
        uniqueAccesses[currentTacticID][0] = true;
    }
    else if(category == "history")
    {
        ui->descriptionButton->setEnabled(true);
        ui->funFactsButton->setEnabled(true);
        ui->historyButton->setEnabled(false);
        uniqueAccesses[currentTacticID][1] = true;
    }
    else
    {
        ui->descriptionButton->setEnabled(true);
        ui->funFactsButton->setEnabled(false);
        ui->historyButton->setEnabled(true);
        uniqueAccesses[currentTacticID][2] = true;
    }

    verifyQuizButtonStatus();
}

void MainWindow::verifyQuizButtonStatus()
{
    // Checks if the user has visited all three categories at least once before enabling the quiz for the level.
    if(!enabledQuiz[currentTacticID])
    {
        int totalUniqueAccesses = 0;
        for(bool uniqueAccess : uniqueAccesses[currentTacticID])
            if(uniqueAccess)
                totalUniqueAccesses++;

        if(totalUniqueAccesses == 3)
        {
            ui->quizButton->setEnabled(true);
            enabledQuiz[currentTacticID] = true;
        }
    }

    /* This checks for when the user jumps from an incomplete tactic level back to one they have already fully
       visited so the quiz button becomes re-enabled. */
    if(!ui->quizButton->isEnabled() && enabledQuiz[currentTacticID])
        ui->quizButton->setEnabled(true);

    /* This checks for when the user jumps from a complete tactic level to one they have not yet
       fully visited, so the quiz button becomes disabled. */
    else if(ui->quizButton->isEnabled() && !enabledQuiz[currentTacticID])
        ui->quizButton->setEnabled(false);
}

void MainWindow::updateTheme(QString buttonAndContentBoxColor, QString scrollColor, QString categoryBoxColor, QString generalBackgroundColor)
{
    //updates theme of the central UI and its various components, to given colors.
    for(QPushButton* button : tacticButtons)
    {
        if(button->styleSheet().endsWith(" font-weight: bold;"))
            button->setStyleSheet(buttonAndContentBoxColor + " font-weight: bold;");
        else
            button->setStyleSheet(buttonAndContentBoxColor);
    }

    ui->freeplay->setStyleSheet(buttonAndContentBoxColor);
    ui->descriptionButton->setStyleSheet(buttonAndContentBoxColor);
    ui->historyButton->setStyleSheet(buttonAndContentBoxColor);
    ui->funFactsButton->setStyleSheet(buttonAndContentBoxColor);
    ui->quizButton->setStyleSheet(buttonAndContentBoxColor);

    ui->categoryContainer->setStyleSheet(categoryBoxColor);
    ui->tacticScrollArea->setStyleSheet(scrollColor);
    ui->textBoxContainer->setStyleSheet(scrollColor);
    ui->scrollAreaWidgetContents->setStyleSheet(scrollColor);
    ui->textLayout->setStyleSheet(buttonAndContentBoxColor);
    ui->colorPalette4Frame->setStyleSheet(generalBackgroundColor);
}

void MainWindow::clearQLabels()
{
    // removes soldier objects
    for(auto *soldier : listOfSoldierLabels)
    {
        delete soldier;
    }
    listOfSoldierLabels.clear();
}

void MainWindow::receiveStartFreePlayMode()
{
    // disables all other tactic buttons while in free play
    for(auto tacticButton : tacticButtons)
        tacticButton->setEnabled(false);

    // sets up all UI elements for the freeplay mode
    ui->infoFrame->setVisible(false);
    ui->freePlayBackground->setVisible(true);
    ui->freeplay->setEnabled(false);
    ui->playButton->setVisible(false);
    updateTheme("background-color: rgb(224,255,210);",
                "background-color: rgb(150,172,135);",
                "background-color: rgb(90,123,94);",
                "background-color: rgb(15,234,195);");
}

void MainWindow::receiveTogglePlaceAllyTool()
{
    selectTool(ui->placeAllyButton, QVector<QPushButton*>{ui->setTrajectoryPoint, ui->placeEnemyButton});
}

void MainWindow::receiveTogglePlaceEnemyTool()
{
    selectTool(ui->placeEnemyButton, QVector<QPushButton*>{ui->setTrajectoryPoint, ui->placeAllyButton});
}

void MainWindow::receiveToggleTrajectoryTool()
{
    selectTool(ui->setTrajectoryPoint, QVector<QPushButton*>{ui->placeAllyButton, ui->placeEnemyButton});
}

void MainWindow::deselectAllTools()
{
    selectTool(nullptr, QVector<QPushButton*>{ui->setTrajectoryPoint, ui->placeEnemyButton, ui->placeAllyButton});
}

void MainWindow::selectTool(QPushButton* enabledTool, QVector<QPushButton*> disabledTools)
{
    //sets all non-selected tools to default color
    if(enabledTool == nullptr)
    {
        for(auto disabledTool : disabledTools)
            disabledTool->setStyleSheet("");
    }
    //sets selected tool color to gray
    else if(enabledTool->styleSheet() == "")
    {
        enabledTool->setStyleSheet("QPushButton {background-color: rgb(105,105,105);}");

        for(auto disabledTool : disabledTools)
            disabledTool->setStyleSheet("");
    }
    else
        enabledTool->setStyleSheet("");
}

void MainWindow::getPlayableSoldierData(int ID)
{
    if(isFreeSimStepPlaying)
        return;

    ui->soldierName->setText(QString::number(ID));
    emit sendClickedSoldierID(ID);
    // determines if the set trajectory button is enabled
    if(!ui->setTrajectoryPoint->isEnabled())
        ui->setTrajectoryPoint->setEnabled(true);

    // sets the place ally button to its default color showing it was not selected
    if(ui->placeAllyButton->styleSheet() != "")
    {
        ui->placeAllyButton->setStyleSheet("");
        emit setNoActiveTool();
    }
    // sets the place enemy button to its default color showing it was not selected
    else if(ui->placeEnemyButton->styleSheet() != "")
    {
        ui->placeEnemyButton->setStyleSheet("");
        emit setNoActiveTool();
    }

    if(currentlyClickedSoldierID != ID)
    {
        // adjusts the soldier point display to be nothing when selecting a point
        currentlyClickedSoldierID = ID;
        ui->coordinates->setText("---");
        if(ui->setTrajectoryPoint->styleSheet() != "")
        {
            ui->setTrajectoryPoint->setStyleSheet("");
            emit setNoActiveTool();
        }
    }
}

void MainWindow::receiveTrajectoryPoint(QPoint trajectoryPoint)
{
    // gets the coordinates and displays it on UI
    ui->coordinates->setText("(" + QString::number(trajectoryPoint.x()) +
                             ", " + QString::number(trajectoryPoint.y()) + ")");

    // creates a targe label to show where you have clicked
    QLabel* trajectoryTarget = new QLabel("", this->centralWidget());

    trajectoryTarget->size() = QSize(25, 25);
    trajectoryTarget->setPixmap(QPixmap(":/target.png"));
    trajectoryTarget->move(trajectoryPoint.x() - 12.5, trajectoryPoint.y() - 12.5);
    trajectoryTarget->show();

    QTimer::singleShot(200, this, [trajectoryTarget]{delete trajectoryTarget;});
}

void MainWindow::receiveToggleToolStatus(bool isEnabled)
{
    if(!isEnabled)
    {
        ui->setTrajectoryPoint->setEnabled(false);
        currentlyClickedSoldierID = -1; // set the currently clicked soldier to an invalid value to show no soldier is selected
        ui->soldierName->setText("None");
        ui->coordinates->setText("---");
        isFreeSimStepPlaying = true;
    }
    else
        isFreeSimStepPlaying = false;

    // adjusts whether the buttons are enabled based on the based in boolean value
    ui->freeSimPlayButton->setEnabled(isEnabled);
    ui->placeAllyButton->setEnabled(isEnabled);
    ui->placeEnemyButton->setEnabled(isEnabled);
    ui->setTrajectoryPoint->setEnabled(isEnabled);
    ui->resetAnimationButton->setEnabled(isEnabled);
    ui->endFreePlayButton->setEnabled(isEnabled);
}

void MainWindow::resetFreeSim()
{
    deselectAllTools();
    currentlyClickedSoldierID = -1; // sets current soldier ID to an invalid value, showing no soldier is selected
    ui->setTrajectoryPoint->setEnabled(false);
    ui->soldierName->setText("None");
    ui->coordinates->setText("---");
    isFreeSimStepPlaying = false;

    QString senderName = sender()->objectName();
    if(senderName == "resetAnimationButton")
        emit sendResetFreeSim();
    else
    {
        emit sendEndFreePlay();
        enableNormalGameMode(); // allows user to select pre made tactics after free play is over
    }
}

void MainWindow::toggleTacticButtons()
{
    // Just need to check if one tactic is enabled, since if one is they all will be.
    if(ui->tactic1->isEnabled())
    {
        for(auto tacticButton : tacticButtons)
            tacticButton->setEnabled(false);

        ui->freeplay->setEnabled(false);
        isAnimationPlaying = true;
        emit sendStartAnimation();
    }
    else
    {
        for(auto tacticButton : tacticButtons)
            tacticButton->setEnabled(true);

        if(isFreePlayUnlocked)
            ui->freeplay->setEnabled(true);

        isAnimationPlaying = false;
    }
}

void MainWindow::enableNormalGameMode()
{
    for(auto tacticButton : tacticButtons)
        tacticButton->setEnabled(true);

    ui->infoFrame->setVisible(true);
    ui->freePlayBackground->setVisible(false);
    ui->freeplay->setEnabled(true);
    ui->playButton->setVisible(true);
}

void MainWindow::receiveEnableFreePlayButton()
{
    if(!isAnimationPlaying)
        ui->freeplay->setEnabled(true);

    isFreePlayUnlocked = true;
}

void MainWindow::receiveCompletedTacticStatus(int tacticID)
{
    QString currentStyleSheet = tacticButtons[tacticID]->styleSheet();
    tacticButtons[tacticID]->setStyleSheet(currentStyleSheet + " font-weight: bold;");
}
