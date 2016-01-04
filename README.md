# Pentago

Placez une bille n’importe où sur le plateau. À la fin de votre tour, faites pivoter un des quatre mini-plateaux d’un quart de tour pour gêner votre adversaire. Pour gagner, alignez cinq billes de votre couleur sur le plateau !

## Protocol

The communication flow between server (S) and clients (C1 and C2) is as follows:

  1. S sends a READY message with each client's color
  2. S sends a PLAYER_TURN message with the current player's color, the PLACE_BALL
     action and the board state
  3. C1 sends a PLAY message with the ball coordinates
  4. S sends a PLAYER_TURN message with the current player's color, the ROTATE action
     and the board state
  5. C1 sends a ROTATE message with the rotation direction
  6. Steps 2. to 5. are repeated N times, the PLAYER_TURN message being sent
     each time with the current player's color
  7. S can send an ERROR message when a game error occurs
  8. S sends a FINISHED message with the color of the winner and the board state
