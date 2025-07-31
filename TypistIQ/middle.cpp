#include "middle.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>     
#include <cstdlib> 
#include <ctime>    

using namespace sf;
using namespace std;

// Constructor: Initializes test state, fonts, default text, and UI layout
TypingTest::TypingTest()
    : testActive(false), testComplete(false), elapsedSeconds(0.0f), wordsPerMinute(0), accuracy(0.0f)
{
    if (!mainFont.loadFromFile("font.ttf"))
    {
        cerr << "Error loading font\n";
    }

    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    // List of paragraphs
    vector<string> paragraphs = {
        "Digital communication has changed the way we connect and share information. From messages and emails to video calls, it's faster and more global than ever. While it helps in collaboration, it also brings issues like screen fatigue and less face-to-face interaction. Learning to use these tools wisely helps us stay clear, connected, and effective in a digital world.",

        "Healthy eating is essential for both physical and mental well-being. A balanced diet with fruits, vegetables, and proteins boosts energy, strengthens the immune system, and supports body repair. On the other hand, junk food and irregular meals can cause fatigue and health issues. Simple habits like staying hydrated and eating mindfully lead to a healthier, more active lifestyle over time.",

        "Time management is a key skill for reaching personal and professional goals. In a world full of distractions, learning to prioritize and manage time wisely helps reduce stress and increase focus. Whether you're a student or a working professional, setting clear goals, avoiding procrastination, and staying organized lead to better results. Good time habits also create space for rest and creativity, making life more balanced and productive."};

    // Randomly select one paragraph
    currentSentence = paragraphs[rand() % paragraphs.size()];

    wrapSentenceText(); // Wrap paragraph to fit UI
    resetTest();        // Reset all test variables
    positionElements(); // Position UI elements
}

// Wraps paragraph text into multiple lines for display
void TypingTest::wrapSentenceText()
{
    const float maxWidth = 740; // Max text width in pixels
    wrappedLines.clear();
    lineStartIndices.clear();

    Text tempText;
    tempText.setFont(mainFont);
    tempText.setCharacterSize(24);

    istringstream iss(currentSentence);
    string word, currentLine;
    int lineStart = 0;

    while (iss >> word)
    {
        string testLine = currentLine + (currentLine.empty() ? "" : " ") + word;
        tempText.setString(testLine);
        if (tempText.getLocalBounds().width < maxWidth)
        {
            currentLine = testLine;
        }
        else
        {
            wrappedLines.push_back(currentLine);
            lineStartIndices.push_back(lineStart);
            lineStart += currentLine.length() + 1;
            currentLine = word;
        }
    }

    if (!currentLine.empty())
    {
        wrappedLines.push_back(currentLine);
        lineStartIndices.push_back(lineStart);
    }
}

// Resets the typing test to its initial state
void TypingTest::resetTest()
{
    playerInput.clear();
    testActive = false;
    testComplete = false;
    elapsedSeconds = 0.0f;
    wordsPerMinute = 0;
    accuracy = 0.0f;

    timerText.setString("60.00s");
    wpmText.setString("WPM: 0");
    accuracyText.setString("Accuracy: 0%");
}

// Positions all SFML elements (title, input area, results)
void TypingTest::positionElements()
{
    const float padding = 30.0f;
    const float width = 800, height = 600;

    // Title
    titleText.setFont(mainFont);
    titleText.setString("TYPING TEST");
    titleText.setCharacterSize(36);
    titleText.setFillColor(Color(100, 150, 255));
    titleText.setPosition((width - titleText.getLocalBounds().width) / 2, padding);

    // Timer
    timerText.setFont(mainFont);
    timerText.setCharacterSize(28);
    timerText.setFillColor(Color(255, 100, 100));
    timerText.setPosition(width - 150, padding);

    // Instructions
    instructionText.setFont(mainFont);
    instructionText.setString("Type the paragraph below:");
    instructionText.setCharacterSize(24);
    instructionText.setFillColor(Color(220, 220, 220));
    instructionText.setPosition(padding, titleText.getPosition().y + 50);

    // Typing area background
    textBackground.setSize(Vector2f(740, 300));
    textBackground.setFillColor(Color(40, 40, 50));
    textBackground.setOutlineThickness(2);
    textBackground.setOutlineColor(Color(100, 150, 255));
    textBackground.setPosition((width - 740) / 2, instructionText.getPosition().y + 40);

    // WPM display
    wpmText.setFont(mainFont);
    wpmText.setCharacterSize(26);
    wpmText.setFillColor(Color(100, 255, 100));
    wpmText.setPosition(width / 2 - 150, height - 60);

    // Accuracy display
    accuracyText.setFont(mainFont);
    accuracyText.setCharacterSize(26);
    accuracyText.setFillColor(Color(100, 200, 255));
    accuracyText.setPosition(width / 2 + 50, height - 60);
}

// Main loop for the typing screen
int TypingTest::run(RenderWindow &window)
{
    while (window.isOpen() && !testComplete && elapsedSeconds < 60.0f)
    {
        handleEvents(window);
        update();
        draw(window);
    }

    // If time ran out and test isn't marked complete, finalize results
    if (elapsedSeconds >= 60.0f && !testComplete)
    {
        calculateResults();
        testComplete = true;
    }

    return 0;
}

// Handles keyboard and window events
void TypingTest::handleEvents(RenderWindow &window)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
        }

        // Start typing and begin timer on first keypress
        if (event.type == Event::TextEntered && !testComplete)
        {
            if (!testActive && event.text.unicode != ' ')
            {
                testActive = true;
                startTime = chrono::steady_clock::now();
            }

            // Handle backspace
            if (event.text.unicode == '\b' && !playerInput.empty())
            {
                playerInput.pop_back();
            }
            // Accept normal characters (ignore enter)
            else if (event.text.unicode < 128 && event.text.unicode != '\r')
            {
                playerInput += static_cast<char>(event.text.unicode);
            }
        }
    }
}

// Updates timer and performance stats while typing
void TypingTest::update()
{
    if (testActive && !testComplete)
    {
        updateTimer();
    }
}

// Updates countdown timer and calculates WPM + accuracy
void TypingTest::updateTimer()
{
    auto now = chrono::steady_clock::now();
    elapsedSeconds = chrono::duration<float>(now - startTime).count();

    float remaining = max(0.0f, 60.0f - elapsedSeconds);
    stringstream ss;
    ss << fixed << setprecision(2) << remaining << "s";
    timerText.setString(ss.str());

    static float lastUpdate = 0.0f;
    if (elapsedSeconds - lastUpdate >= 0.5f)
    {
        lastUpdate = elapsedSeconds;

        // Count correct characters
        int correct = 0;
        int length = min(playerInput.length(), currentSentence.length());
        for (int i = 0; i < length; ++i)
        {
            if (playerInput[i] == currentSentence[i])
            {
                correct++;
            }
        }

        // WPM and accuracy calculation
        if (elapsedSeconds > 0)
        {
            wordsPerMinute = static_cast<int>((correct / 5.0f) / (elapsedSeconds / 60.0f));
            accuracy = (playerInput.empty() ? 0 : (static_cast<float>(correct) / playerInput.length()) * 100.0f);
            wpmText.setString("WPM: " + to_string(wordsPerMinute));
            accuracyText.setString("Accuracy: " + to_string(static_cast<int>(accuracy)) + "%");
        }
    }
}

// Final calculation when timer ends
void TypingTest::calculateResults()
{
    int correct = 0;
    int length = min(playerInput.length(), currentSentence.length());
    for (int i = 0; i < length; ++i)
    {
        if (playerInput[i] == currentSentence[i])
        {
            correct++;
        }
    }
    wordsPerMinute = static_cast<int>((correct / 5.0f) / (elapsedSeconds / 60.0f));
    accuracy = (playerInput.empty() ? 0 : (static_cast<float>(correct) / playerInput.length()) * 100.0f);
}

// Renders all test elements: paragraph, timer, WPM, input overlay
void TypingTest::draw(RenderWindow &window)
{
    window.clear(Color(20, 20, 30));

    window.draw(titleText);
    window.draw(timerText);
    window.draw(instructionText);
    window.draw(textBackground);

    Vector2f basePos = textBackground.getPosition() + Vector2f(10, 10);
    float lineHeight = 30.0f;

    // Draw paragraph and user input overlay
    for (size_t i = 0; i < wrappedLines.size(); ++i)
    {
        // Original paragraph line
        Text lineText;
        lineText.setFont(mainFont);
        lineText.setCharacterSize(24);
        lineText.setFillColor(Color(240, 240, 240));
        lineText.setString(wrappedLines[i]);
        lineText.setPosition(basePos.x, basePos.y + i * lineHeight);
        window.draw(lineText);

        // Overlay typed characters (green = correct, underscore = wrong)
        int start = lineStartIndices[i];
        int end = (i + 1 < lineStartIndices.size()) ? lineStartIndices[i + 1] : currentSentence.length();

        string userLine;
        for (int j = start; j < end && j < playerInput.length(); ++j)
        {
            if (playerInput[j] == currentSentence[j])
                userLine += playerInput[j];
            else
                userLine += '_';
        }

        Text typedText;
        typedText.setFont(mainFont);
        typedText.setCharacterSize(24);
        typedText.setFillColor(Color::Green);
        typedText.setString(userLine);
        typedText.setPosition(basePos.x, basePos.y + i * lineHeight);
        window.draw(typedText);
    }

    // Draw WPM and Accuracy stats
    window.draw(wpmText);
    window.draw(accuracyText);
    window.display();
}
