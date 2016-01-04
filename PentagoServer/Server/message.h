#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <QtNetwork>
#include "type.h"
#include <string>
#include <QVector>
#include "playercolor.h"
#include "business/hole.h"

/*!
 * \brief The Message class
 */
class Message
{
public:

    /*!
     * \brief The GameAction enum a game action to be performed
     */
    enum class GameAction {
        PLACE_BALL,
        ROTATE
    };

    Message();

    /*!
     * \brief Message Constructs a message of the given type
     * \param type the type of the message
     */
    Message(TypeMessage type);

    /*!
     * \brief setPlayerColor sets the Player color
     * \param color
     * \throws std::logic_error if the message is not of TypeMessage::READY,TypeMessage::PLAYER_TURN or TypeMessage::FINISHED
     */
    void setPlayerColor(PlayerColor color);

    /*!
     * \brief setGameAction sets the gameAction of the message
     * \param action TypeMessage::PLAYER_TURN
     * \throws std::logic_error if the message is not of TypeMessage::PLAYER_TURN
     */
    void setGameAction(GameAction action);

    /*!
     * \brief setBoard sets the board of the message
     * \param board a representation of a Pentago bard
     * \throws std::logic_error if the message is not of TypeMessage::BOARD_UPDATE,TypeMessage::PLAYER_TURN,TypeMessage::FINISHED)
     */
    void setBoard(QVector<QVector<PlayerColor>> board);

    /*!
     * \brief setLine sets the line where the player will place the ball
     * \param line
     * \throws std::logic_error if the message is not of TypeMessage::PLAY
     */
    void setLine(int line);

    /*!
     * \brief setColumn sets the column where the player will place the ball
     * \param column
     * \throws std::logic_error if the message is not of TypeMessage::PLAY
     */
    void setColumn(int column);

    /*!
     * \brief setMiniBoardIndice sets the miniboard number that the player wants to rotate
     * \param indice
     * \throws std::logic_error if the message is not of TypeMessage::ROTATE
     */
    void setMiniBoardIndice(int indice);

    /*!
     * \brief setClockwiseRotation sets the direction in which the player will rotate the mini board
     * \param clockwise
     * \throws std::logic_error if the message is not of TypeMessage::ROTATE
     */
    void setClockwiseRotation(bool clockwise);

    /*!
     * \brief setError sets the error in the message
     * \param error
     * \throws std::logic_error if the message is not of TypeMessage::ERROR
     */
    void setError(QString error);

    /*!
     * \brief getType
     * \return the type of the message
     */
    TypeMessage getType() const;

    /*!
     * \brief getPlayerColor
     * \return the PlayerColor of the message
     */
    PlayerColor getPlayerColor() const;

    /*!
     * \brief getGameAction
     * \return the GameAction of the player
     */
    GameAction getGameAction() const;

    /*!
     * \brief getBoard
     * \return the board of the message
     */
    QVector<QVector<PlayerColor>> getBoard() const;

    /*!
     * \brief getLine
     * \return the line of the message
     */
    int getLine() const;

    /*!
     * \brief getColumn
     * \return the column of the message
     */
    int getColumn() const;

    /*!
     * \brief getMiniBoardIndice
     * \return the miniboard number of the message
     */
    int getMiniBoardIndice() const;

    /*!
     * \brief isClockwiseRotation
     * \return true if the roation is clockwise false otherwise
     */
    bool isClockwiseRotation() const;

    /*!
     * \brief getError
     * \return the error of the message
     */
    QString getError() const;

    /*!
     * \brief convertBoard converts a board from the business model to a board to be sent to clients
     * \param vec the board from the model
     * \return the converted board
     */
    static QVector<QVector<PlayerColor>> convertBoard(std::vector<std::vector<Hole>> &vec);

private:
    TypeMessage type;                           /*!< the type of the message*/
    PlayerColor playerColor;                    /*!< the player color to be included in the message*/
    GameAction gameAction;                      /*!< the game action to be included in the message*/
    QVector<QVector<PlayerColor>> board;        /*!< the board to be include in the message*/
    int line;                                   /*!< the line number of the board to be included in the message*/
    int column;                                 /*!< the column number of the board to be included in the message*/
    int miniBoardIndice;                        /*!< the miniboard number to be included in the message*/
    bool clockwise;                             /*!< the direction to be included in the message */
    QString error;                              /*!< the error message to be included in the message*/
};

/*!
 * \brief operator << Injects a GameAction inside a QDataStream
 * \param flux the output object
 * \param action the input object
 * \return
 */
inline QDataStream &operator<<( QDataStream &flux, const Message::GameAction &action)
{
    switch (action) {
    case Message::GameAction::PLACE_BALL:
        flux << 0;
        break;
    case Message::GameAction::ROTATE:
        flux << 1;
        break;
    }

    return flux;
}

/*!
 * \brief operator >> Unboxes a QDataStream object inside a GameAction
 * \param flux the input object
 * \param action the output object
 */
inline void operator>>( QDataStream &flux, Message::GameAction &action)
{
    int actionId;
    flux >> actionId;
    switch (actionId) {
    case 0:
        action = Message::GameAction::PLACE_BALL;
        break;
    case 1:
        action = Message::GameAction::ROTATE;
        break;
    }
}

inline QDataStream &operator<<( QDataStream &flux, const Message &message)
{
    flux << message.getType();
    switch (message.getType()) {
    case TypeMessage::READY:
        flux << message.getPlayerColor();
        break;
    case TypeMessage::PLAYER_TURN:
        flux << message.getPlayerColor();
        flux << message.getGameAction();
        flux << message.getBoard();
        break;
    case TypeMessage::BOARD_UPDATE:
        flux << message.getBoard();
        break;
    case TypeMessage::PLAY:
        flux << message.getLine();
        flux << message.getColumn();
        break;
    case TypeMessage::ROTATE:
        flux << message.getMiniBoardIndice();
        flux << message.isClockwiseRotation();
        break;
    case TypeMessage::FINISHED:
        flux << message.getPlayerColor();
        flux << message.getBoard();
        break;
    case TypeMessage::ERROR:
        flux << message.getError();
        break;
    }

    return flux;
}

inline void operator>>( QDataStream &flux, Message & msg)
{
    TypeMessage type;
    flux >> type;

    msg = Message(type);
    switch (type) {
    case TypeMessage::READY:
    {
        PlayerColor color;
        flux >> color;
        msg.setPlayerColor(color);
    }
        break;
    case TypeMessage::PLAYER_TURN:
    {
        PlayerColor color;
        Message::GameAction action;
        QVector<QVector<PlayerColor>> board;
        flux >> color;
        flux >> action;
        flux >> board;
        msg.setPlayerColor(color);
        msg.setGameAction(action);
        msg.setBoard(board);
    }
        break;
    case TypeMessage::BOARD_UPDATE:
    {
        QVector<QVector<PlayerColor>> board;
        flux >> board;
        msg.setBoard(board);
    }
        break;
    case TypeMessage::PLAY:
        int line, column;
        flux >> line >> column;
        msg.setLine(line);
        msg.setColumn(column);
        break;
    case TypeMessage::ROTATE:
        int miniBoardIndice;
        bool isClockwiseRotation;
        flux >> miniBoardIndice;
        flux >> isClockwiseRotation;
        msg.setMiniBoardIndice(miniBoardIndice);
        msg.setClockwiseRotation(isClockwiseRotation);
        break;
    case TypeMessage::FINISHED:
    {
        PlayerColor color;
        QVector<QVector<PlayerColor>> board;
        flux >> color;
        flux >> board;
        msg.setPlayerColor(color);
        msg.setBoard(board);
    }
        break;
    case TypeMessage::ERROR:
        QString error;
        flux >> error;
        msg.setError(error);
        break;
    }
}

#endif // MESSAGE_H
