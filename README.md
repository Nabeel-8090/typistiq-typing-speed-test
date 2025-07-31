# TypistIQ - Typing Speed Test Application

## About the Project
**TypistIQ** is a fast and clean desktop typing test app built using C++ and SFML.
<br>
Challenge yourself with randomly selected paragraphs, track your **WPM**, **accuracy**, and get smart feedback on your typing speed.

## How to Play
* The test lasts 60 seconds
* A random paragraph will appear
* Start typing as accurately and quickly as possible
* Real-time stats: WPM and Accuracy
* After time is up, you'll see your results and feedback

## 🛠 Installation & Running

### 1️⃣ Clone or Download
Run the following command in the terminal to clone the repository:
```sh
git clone https://github.com/YOUR_USERNAME/TypistIQ.git
cd TypistIQ
```
Alternatively, download the ZIP file and extract it.

### 2️⃣ Requirements
* C++17 or later compiler
* SFML 2.6+
* Windows (tested) or Linux

### 3️⃣ Compile & Run (Windows - MinGW / MSYS2)
```sh
g++ main.cpp front.cpp middle.cpp last.cpp -o TypistIQ -I<path_to_SFML>\include -L<path_to_SFML>\lib -lsfml-graphics -lsfml-window -lsfml-system
```
Replace <path_to_SFML> with your actual SFML folder path.
Then run:
```sh
TypistIQ.exe
```




