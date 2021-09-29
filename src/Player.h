#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <mutex>
#include <algorithm>

template <class T>
class MessageQueue
{
public:
    void send(T &&msg);
    T receive();
    void print();

private:
    std::deque<T> _queue;
    std::condition_variable _cond;
    std::mutex _mutex;
};

class Player
{
public:
    Player(int id, std::shared_ptr<MessageQueue<std::string>> queue, int &playsNext);
    void play();
    void calculateNextMove();
    std::string calculateInputForNextPlayer(std::string move);

private:
    int _id;
    int  &_playsNext;
    std::mutex _mutex;
    std::shared_ptr<MessageQueue<std::string>> _queue; //  Non-owning
};

#endif