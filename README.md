# Coloretto

A Coloretto game using C++ to complete. Don't worry about that you didn't play it before, you can find the rule easily on the Net!!!

## Building the Project

* Compile the code

```

gcc -o <name> game.cpp

```
## Usage
* Run the game

```

./<name>

```

## Result

* If game successfully open, you'll see the interface like below.

```

Welcome to the Coloretto Game.

Please decide the number of players [one is you,and the other(s) is AI]
It is restricted to play by 3~5 people,so don't enter other number of people.
The number of players :5

Please decide the level of AI
        紅     橙     黃     綠     藍     金     銀     彩     加
1 |      0      0      0      0      0      0      1      0      0
2 |      1      0      0      0      0      0      0      0      0
3 |      0      0      0      0      0      1      0      0      0
4 |      0      1      0      0      0      0      0      0      0
5 |      0      0      1      0      0      0      0      0      0

綠  加  彩  無  加  加  藍  金  加  橙
綠  銀  綠  黃  無  加  綠  金  紅  藍
金  無  綠  無  金  橙  金  銀  無  銀
彩  銀  銀  加  黃  金  加  藍  銀  橙
綠  黃  綠  藍  藍  藍  橙  綠  紅  綠
金  藍  藍  彩  加  藍  紅  橙  銀  紅
黃  終  黃  加  加  橙  金  紅  銀  紅
黃  黃  紅  紅  橙  橙  黃

Now is player 1's turn.

Because there is no line to take,so you can only draw the card.
You decide to draw the card.
The new-drawed card is "綠"

Please decide which line to place.
    A    B    C    D    E
------------------------------
   無   無   無   無   無
   無   無   無   無   無
   無   無   無   無   無
The line you choose to place :

```
