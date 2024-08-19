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

* Coverage 97% by Unit tests (You also can check it by `make test` and `make gcov-report`)

 <img src="images/LCOV.png" alt="Screenshot_of_LCOV" width="630"/>

* Documentation done with Doxyfile (`make dvi`)

<img src="images/Doc.png" alt="Screenshot_of_Doc" width="300"/>


* Realized with principle of finite state machine
  
<img src="images/FSM.png" alt="Screenshot_of_FSM" width="630"/>

* Implementation backend and frontend parts separately
  
* Loading and saving record in invisible file

* All 7 types color tetromino

<img src="images/All_Tetromino.png" alt="Screenshot_of_All_Tetromino" width="630"/>

* Information about game over and the ability to restart the game

![Screenshot_of_Start](images/Start.png)
![Screenshot_of_End](images/Game_over.png)
