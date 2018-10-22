# Code for driving an Arduino Card

## Summary:
This documentation covers these items listed below:

* [Features](#features)
* [Installing](#under-development)
* [LCD Parallel Sequency](#lcd-parallel-sequency)
* [How to configure Wheels](#how-to-configure-wheels)
* [Cables](#cables)
 
## Features:
- Go Forward and Backward
- Turn right and left without differential
- Avoid wall hits and turn

## Under development:
- Bluetooth

## LCD Parallel Sequency
-Verde Vazio Branco Preto Roxo Azul Verde Amarelo Laranja Vermelho (Acima Laranja)
-marrom vermelho laranja amarelo
-rxd    txd      gnd     5v
-txd   rxd    -   +

## How to configure Wheels
Search for `acelerar()` function
```
 digitalWrite(MT_IN_1, LOW);  // 1st
 digitalWrite(MT_IN_2, HIGH); //2nd
 digitalWrite(MT_IN_3, HIGH); // 3nd
 digitalWrite(MT_IN_4, LOW);  // 4th
```

- Stop: 4 LOW or 4 HIGH
- Forward: 2nd and 3rt HIGH, 1nd and 4th LOW
- Turn right: 1st and 3rt HIGH, 2nd and 4th LOW or 1st, 2nd and 3rt HIGH, 4th LOW
- Go back: 3rt and 4th HIGH, 1st and 2nd LOW
- Turn left: 2nd,3rt and 4th HIGH, 1st LOW
- Back left: 1st, 3rt and 4th HIGH, 2nd LOW
- Back right: 1st, 2nd and 4th HIGH, 3nd LOW

## Cables

Configure the right digital port for each Motor.

```
// Motor A
#define MT_EN_A 2
#define MT_IN_1 3 // Wheel
#define MT_IN_2 4 // Wheel

// Motor B
#define MT_EN_B 7 
#define MT_IN_3 5 // Wheel
#define MT_IN_4 6 // Wheel

```

Bluetooth adapter: Xinda keyes - IR receiver
