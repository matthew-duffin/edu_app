/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Header implementation of the quiz window functionality for the tactics program.
                Handles the connection logic between the model and the main window.
                Each tactic has a unique corresponding quiz.
*/

#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include "model.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class QuizWindow; }
QT_END_NAMESPACE

/**
 * @brief The QuizWindow class : A QWidget that creates a seperate window for handling quizzes.
 */
class QuizWindow : public QWidget
{
    Q_OBJECT

private:
    /**
     * @brief ui : Default UI object.
     */
    Ui::QuizWindow *ui;

    /**
     * @brief backgroundStyleSheets : QVector of QStrings used to change the quiz UI background color.
     */
    QVector<QString> backgroundStyleSheets;

    /**
     * @brief buttonStyleSheets : QVector of QStrings used to change the quiz UI button colors.
     */
    QVector<QString> buttonStyleSheets;

    /**
     * @brief tacticID : Integer value that tracks the current tactic ID. Used with backgroundStyleSheets and buttonStyleSheets
     */
    int tacticID;

public:

    /**
     * @brief QuizWindow : Constructor for QuizWindow.
     * @param model : Model object that handles logic.
     */
    explicit QuizWindow(Model& model, QWidget *parent = nullptr);
    ~QuizWindow();

public slots:

    /**
     * @brief wrongAnswer : Changes the text of choice in the UI to signify a wrong choice.
     * @param choice : Integer value representing the question choice as an index.
     */
    void wrongAnswer(int choice);

    /**
     * @brief changeQuizUI : Takes in information from the model and updates the corresponding quiz UI elements.
     *                       This method will be called whenever the user changes question.
     * @param currentTacticID : Integer value representing the currently selected tactic.
     * @param questionIndex : Integer value representing the current question index.
     * @param question : QString value representing the current question.
     * @param choice1 : QString value representing the first choice.
     * @param choice2 : QString value representing the second choice.
     * @param choice3 : QString value representing the third choice.
     * @param choice4 : QString value representing the fourth choice.
     */
    void changeQuizUI(int currentTacticID, int questionIndex, QString question, QString choice1, QString choice2, QString choice3, QString choice4);

    /**
     * @brief quizCompletion : Updates the quiz UI when user achieves 100% completion the current quiz.
     */
    void quizCompletion();

    /**
     * @brief resetQuizUILabels : Resets certain quiz UI elements to their default or blank values.
     */
    void resetQuizUILabels(int currentTacticID, int questionIndex, QString question, QString choice1, QString choice2, QString choice3, QString choice4, bool quizCompletion);
};

#endif // QUIZWINDOW_H
