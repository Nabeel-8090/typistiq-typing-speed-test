#ifndef TYPING_TEST_HPP
#define TYPING_TEST_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <chrono>

using namespace sf;
using namespace std;

class TypingTest {
public:
    TypingTest(); // Constructor to initialize everything
    int run(RenderWindow& window); // Main function to start the typing test

    // Getters for test results
    int getWPM() const { return wordsPerMinute; }
    float getAccuracy() const { return accuracy; }
    float getElapsedTime() const { return elapsedSeconds; }

private:
    // Load all predefined paragraphs
    void loadSentences();

    // Randomly pick one sentence for the test
    void selectRandomSentence();

    // Break the sentence into multiple lines for wrapping
    void wrapSentenceText();

    // Reset variables to restart the test
    void resetTest();

    // Adjust positions of all UI elements
    void positionElements();

    // Handle keyboard and window events
    void handleEvents(RenderWindow& window);

    // Update input, check correctness
    void update();

    // Keep track of time
    void updateTimer();

    // Calculate final WPM and accuracy
    void calculateResults();

    // Draw all visuals to the screen
    void draw(RenderWindow& window);

    // Fonts and text elements
    Font mainFont;
    Text titleText;
    Text timerText;
    Text instructionText;
    Text sentenceText;
    Text wpmText;
    Text accuracyText;

    // UI background
    RectangleShape textBackground;

    // Sentences and input
    vector<string> sentences;
    string currentSentence;
    string playerInput;
    vector<string> wrappedLines;
    vector<int> lineStartIndices;

    // Typing test state
    bool testActive;
    bool testComplete;
    float elapsedSeconds;
    int wordsPerMinute;
    float accuracy;
    chrono::steady_clock::time_point startTime;
};

#endif
