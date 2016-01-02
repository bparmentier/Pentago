# Pentago


Placez une bille n’importe où sur le plateau. À la fin de votre tour, faites pivoter un des quatre mini-plateaux d’un quart de tour pour gêner votre adversaire. Pour gagner, alignez cinq billes de votre couleur sur le plateau !
##### Protocol
The communication flow between server (S) and clients (C1 and
C2) is as follows:
  1. S sends a READY message with each client's color
  2. S sends a PLAYER_TURN message with the current player
  3. C1 sends a PLAY message with the ball coordinates
  4. S sends a BOARD_UPDATE message with the state of the board
  5. C1 sends a ROTATE message with the rotation direction
  6. S sends a BOARD_UPDATE message with the state of the board
  7. S sends a PLAYER_TURN message with the new current player
  8. Steps 2. to 6. are repeated N times
  9. S can send an ERROR message when a game error occurs
  10. S sends a FINISHED message with the color of the winner
