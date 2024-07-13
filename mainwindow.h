/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Header implementation of the mainwindow for the tactics program.
                Handles displaying the UI elements for each individual tactic
                like information or push buttons as well as the UI elements
                for the free-play mode.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model.h"
#include "quizwindow.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QList>
#include <QPoint>
#include <QString>
#include <QPushButton>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QuizWindow quizWindow;
    bool uniqueAccesses[6][3]{};        // Checks the unique accesses of each category for each tactic.
    bool enabledQuiz[6]{};
    int currentTacticID;
    QVector<QPushButton*> tacticButtons;
    QList<QLabel*> listOfSoldierLabels;
    int currentlyClickedSoldierID;
    bool isFreeSimStepPlaying;
    bool isFreePlayUnlocked;
    bool isAnimationPlaying;

    /**
     * @brief initializeContent : Initializes the content/textbox with the description of the first tactic
     *                            when the program starts.
     */
    void initializeContent();

    /**
     * @brief verifyQuizButtonStatus : Checks whether or not the quiz button should be enabled based off of
     *                                 the unique accesses for each tactic level.
     */
    void verifyQuizButtonStatus();

    /**
     * @brief updateTheme : updates the theme of the U.I. for each tactic level.
     * @param buttonAndContentBoxColor : describes the stylesheet for the button and content/textbox.
     * @param scrollColor : describes the stylesheet for the tactic scroll area.
     * @param categoryBoxColor : describes the stylesheet for the box behind the category buttons.
     * @param generalBackgroundColor : describes the stylesheet for the general background.
     */
    void updateTheme(QString buttonAndContentBoxColor, QString scrollColor, QString categoryBoxColor, QString generalBackgroundColor);

    /**
     * @brief selectTool : Selects a tool of the "Free Play" mode. If the enabled tool is nullptr then no
     *                     tool is active but each of the tools in disabledTools will still have its color
     *                     set to the disabled color background.
     * @param enabledTool : sets the enabled tool button color to the "active" color.
     * @param disabledTools : sets each of the other tools, not the active tool, to the disabled color.
     */
    void selectTool(QPushButton* enabledTool, QVector<QPushButton*> disabledTools);

    /**
     * @brief enableNormalGameMode : helper method which sets up the U.I. elements for the normal game mode
     *                               from the "Free Play" gamemode.
     */
    void enableNormalGameMode();

protected:
    /**
     * @brief mousePressEvent : Event that checks where the mouse was pressed.
     * @param event : holds information like the coordinates of the mouse press location.
     */
    void mousePressEvent(QMouseEvent *event);

public:
    /**
     * @brief MainWindow : Constructor - creates an instance of MainWindow.
     * @param model : holds the backing data and controls logic of the application.
     * @param parent : ignored.
     */
    MainWindow(Model& model, QWidget *parent = nullptr);

    /**
     * @brief ~MainWindow : Destructor - releases resources used at the end of MainWindow's scope.
     */
    ~MainWindow();

    /**
     * @brief moveSoldierLabel : moves the label representing the soldier.
     * @param soldierId : the ID of the soldier.
     * @param x : the x location where the soldier label should move to.
     * @param y : the y location where the soldier label should move to.
     */
    void moveSoldierLabel(int soldierId, int x, int y);

public slots:
    /**
     * @brief changeBackgroundLabel: Sets animation background to image
     * @param image: Background image
     */
    void changeBackgroundLabel(QPixmap image);

    /**
     * @brief makeNewQLabel: Dynamically creates a new label to represent soldier in animation
     * @param pos: Coordinate position
     * @param isEnemy: Represents if soldier is ally or enemy
     * @param isFreePlayEnabled: Represents if in tactic mode or free play mode
     * @param labelID: The label ID
     */
    void makeNewQLabel(QPoint pos, bool isEnemy, bool isFreePlayEnabled, int labelID);

    /**
     * @brief receiveUpdatedContent: Updates view to reflect model after navigating to new window
     * @param content: Text box content
     * @param category: Which category of information is being requested
     * @param tacticID: id of selected tactic
     */
    void receiveUpdatedContent(QString content, QString category, int tacticID);

    /**
     * @brief clearQLabels: Deletes soldier labels and removes them from view
     */
    void clearQLabels();

    /**
     * @brief deselectAllTools: updates tool button stylesheets to look unselected
     */
    void deselectAllTools();

    /**
     * @brief receiveToggleToolStatus: Toggles tool buttons to be enabled/disabled
     * @param isEnabled: Should buttons be enabled or disabled
     */
    void receiveToggleToolStatus(bool isEnabled);

    /**
     * @brief showQuizWindow : Displays the quiz window.
     */
    void showQuizWindow();

    /**
     * @brief receiveStartFreePlayMode: Updates ui to free play mode ui
     */
    void receiveStartFreePlayMode();

    /**
     * @brief receiveToggleTrajectoryTool: Highlights trajectory tool and unhighlights other tools
     */
    void receiveToggleTrajectoryTool();

    /**
     * @brief receiveTogglePlaceAllyTool: Highlights place ally tool and unhighlights other tools
     */
    void receiveTogglePlaceAllyTool();

    /**
     * @brief receiveTogglePlaceEnemyTool: Highlights place enemy tool and unhighlights other tools
     */
    void receiveTogglePlaceEnemyTool();

    /**
     * @brief getPlayableSoldierData: Updates view and notifies model based on selected soldier
     * @param ID: ID of selected soldier
     */
    void getPlayableSoldierData(int ID);

    /**
     * @brief receiveTrajectoryPoint: Updates ui to show soldier trajectory point
     * @param trajectoryPoint: The soldier's trajectory point
     */
    void receiveTrajectoryPoint(QPoint trajectoryPoint);

    /**
     * @brief resetFreeSim : resets variables used in free sim and switches to normal animation mode
     */
    void resetFreeSim();

    /**
     * @brief toggleTacticButtons : toggles the tactic buttons when starting an animation
     */
    void toggleTacticButtons();

    /**
     * @brief receiveEnableFreePlayButton : enables freeplay ui after animation stops
     */
    void receiveEnableFreePlayButton();

    /**
     * @brief receiveCompletedTacticStatus : bolds the text on tactic buttons when completed
     * @param tacticID : ID of desired tactic
     */
    void receiveCompletedTacticStatus(int tacticID);

signals:

    /**
     * @brief quizSelection : Signals the model to tell the quiz window which quiz to display.
     */
    void quizSelection();

    /**
     * @brief initializeContentBox: Notifies model to send current textbox content
     */
    void initializeContentBox();

    /**
     * @brief onLoad: Initializes ui content on first load
     */
    void onLoad();

    /**
     * @brief sendAnimationMouseCoordinates: Notifies model when mouse pressed on animation
     * @param mouseCoords: Coordinates of mouse press
     * @param ID: ID of currently clicked soldier
     */
    void sendAnimationMouseCoordinates(QPoint mouseCoords, int ID);

    /**
     * @brief sendClickedSoldierID: Notifies model of soldier ID when clicked
     * @param ID: ID of clicked soldier
     */
    void sendClickedSoldierID(int ID);

    /**
     * @brief setNoActiveTool : Notifies model that no tool is selected
     */
    void setNoActiveTool();

    /**
     * @brief sendResetFreeSim : signals model to reset free sim
     */
    void sendResetFreeSim();

    /**
     * @brief sendStartAnimation : signals model to start animation
     */
    void sendStartAnimation();

    /**
     * @brief sendEndFreePlay : signals model to end free play
     */
    void sendEndFreePlay();
};
#endif // MAINWINDOW_H
