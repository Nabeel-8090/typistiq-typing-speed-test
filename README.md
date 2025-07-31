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
Replace **<path_to_SFML>** with your actual SFML folder path.
<br>
Then run:
```sh
TypistIQ.exe
```

### 4️⃣ Compile & Run (Linux)
```sh
g++ main.cpp front.cpp middle.cpp last.cpp -o TypistIQ -lsfml-graphics -lsfml-window -lsfml-system
./TypistIQ
```


## Features
✅ 60-second typing challenge
✅ Random paragraph generation
✅ Real-time WPM & accuracy display
✅ Clean feedback screen
✅ Modular OOP architecture (7 files)
✅ Built with SFML for smooth rendering
✅ Custom fonts and minimal UI
✅ Light and responsive keyboard-based interface

## Contributing
Want to improve TypistIQ?<br>
You're welcome to:
* ⭐ Star the repo
* 🛠 Fork it
* 📌 Open issues / suggestions
* 🔁 Submit PRs

## License
This project is open-source under the **MIT License**.

## 🔥 Enjoy Typing!
If you like this project, don't forget to give it a ⭐ on GitHub!<br>
Happy Typing! ⌨️😊






