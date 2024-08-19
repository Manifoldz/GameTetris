## 🧩 GameTetris

### The GameTetris is a terminal-version of the popular russian game "Tetris"
🚀 Developed in a structured programming style in pure C language.

![Screenshot_of_Game](images/Game.png)

### 🏁 Start the Game

* To start the game - use `make install` and after `make start`.

### 🕹️ Game controls

* <- | -> to move the tetromino
     v
* "Enter" - start the game
* "p" - pause
* "Space" - rotate the tetromino
* "Esc" - exit the game

### ℹ️ Info

* Coverage 95% by Unit tests
* You also can check it by `make test` and `make gcov-report`

* Documentation done with Doxyfile

* Realized with principle of finite state machine
* ![Screenshot_of_Game](FSM.png)

* Implementation backend and frontend parts separatly
* Loading and saving record in invisible file

* All 7 Types Tetromino
* ![Screenshot_of_Game](images/All_Tetromino.png)
* ![Screenshot_of_Game](images/Start.png)
![Screenshot_of_Game](images/Game_over.png)
