# RunningFast_PokerGame_C

## Aim: 
To create a popular Chinese poker game, Running fast by using AI logics so that player could play this game with computer.  

# How to reach: 
AI is designed by fuzzy logic, binary tree, looped weighted function, Guassian Mix model, etc.

The program consists 2 parts: the modules that contains all the game logic and AI algorithm, and the user interface developed using Java Swing. They communicate with each other through a TCP connection. The game is built from scratch without any third-party library.  

The rule of game:
Running Fast uses one pack of the cards, but it removes three jokers, two card 2s and one ace, which in total has 48 cards, 13 spades, 13 hearts, 13 diamonds, and 13 clubs. Game can be played for 3 players or 2, and for each player, it has 18 cards on their hands. The colour and sign of cards is not considered in the game, only the value matters, which has the following orders.  
3< 4< 5< 6< 7< 8< 9< 10< j< Q< K< A< 2< Bomb.  
Where Bomb is four identical value of cards, such as 5555, etc.  

Patterns:  
Single cards: e.g. 3  
One pair: e.g. 3 3  
Multi-Pairs: multiple pairs with consecutive points. e.g. 3 3 4 4, 5 5 6 6 7 7.  
Three of a kind: e.g. 3 3 3  
Full House: A composite of a three-of-a-kind combination and a pair. Ordered by the rank of the triple, regardless of the pair. e.g. 3 3 3 4 4.  
Straight: Any 5 or more cards in a row. e.g. 3 4 5 6 7.  
Bomb: Any 4 cards of same point. e.g. 3 3 3 3.  

Number 3 is the smallest value and Bomb is the biggest pattern. The definition of pattern will be explained later. As it ruled, for each turn, only one pattern of cards can be played. Player has to pass if they do not have bigger values cards than opponent’s (AI). In total, we have 7 categories and 18 associating patterns. We say category and pattern here, it means that Single card, like 3, 5, etc.; One pair, two cards with same value, like 33, 66, etc.; Multi-pair, as least three or more consecutive cards, like 44 55 66, ect.; A straight, at least five or more consecutive cards, like 34567, ect; Three of a kind, three cards with the same value, like 333, 777, ect; Full house, three cards of the same value with two cards of same value, like 33344, 66688, etc.; Bomb, four cards with the same value, like 4444, 5555, etc., Bomb is the biggest pattern, it can beat all the other patterns exclude the bigger value other bombs. Now, based on the value ordering, we use 0-12 to represent 13 spade cards, 13-25 to represent 13 hearts and so forth until 52 to represent club 2. Remember three cards of number 2 and one Ace card are removed, and number 53 is used for pass button. For the validation of player or AI’s move, we uses a vector to represent the move and check if it satisfies the rules.

Architecture of the project:  
![Screen Shot 2023-05-09 at 2 50 03 PM](https://github.com/btbbtzhang/RunningFast_PokerGame_C/assets/34163897/adbf5183-28d9-4364-b259-6d9ac5d3a452)


The relations between modules:  
![Screen Shot 2023-05-09 at 2 42 57 PM](https://github.com/btbbtzhang/RunningFast_PokerGame_C/assets/34163897/ddd08bb7-31de-4c5e-b1b5-d43f77c380ce)


Artifical Intelligence working structure:  
![Screen Shot 2023-05-09 at 2 32 47 PM](https://github.com/btbbtzhang/RunningFast_PokerGame_C/assets/34163897/61c2a141-c6e7-4bd9-8db3-dd18c5e61b00)

# Result:
Demonstration of Demo:  
![Screen Shot 2023-05-09 at 2 44 34 PM](https://github.com/btbbtzhang/RunningFast_PokerGame_C/assets/34163897/a2d73813-a075-4a78-a1d0-355989817156)
