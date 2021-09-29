#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>

#include "Player.h"

template <typename T>
T MessageQueue<T>::receive()
{
    // perform modification of _queue under the lock
    std::unique_lock<std::mutex> myLock(_mutex);

    // pass unique lock to condition variable
    // check that new data is really available via !_queue.empty() to avoid issuing wait() in case of spurious wake up
    _cond.wait(myLock, [this] { return !_queue.empty(); });

    // get last element from _queue
    T msg = std::move(_queue.back());
    _queue.pop_back();

    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // perform modification of _queue under the lock
    std::lock_guard<std::mutex> myLock(_mutex);

    // add msg to queue
    _queue.push_back(std::move(msg));

    // notify client after pushing new message into deque
    _cond.notify_one(); 
}

template <typename T>
void MessageQueue<T>::print()
{
    // lock console
    std::lock_guard<std::mutex> myLock(_mutex);
    std::cout << _queue.back() << std::endl;
}

// constructor
Player::Player(int id, std::shared_ptr<MessageQueue<std::string>> _queue, int &playsNext) : 
    _id(id), _queue{_queue}, _playsNext{playsNext} {}

// calculates the optimal next move for this player
void Player::calculateNextMove()
{
    // This equals the main() function of the CodinGame game after the inputs were read in correctly
    // TODO: Implement
}

// returns the next player's input based on the current player's move
std::string Player::calculateInputForNextPlayer(std::string move)
{
    return move; // TODO: Implement
}

void Player::play()
{
    while (true)
    {
        if (_playsNext == _id) // check that it is this player's turn
        {
            // perform entire move under the lock
            std::lock_guard<std::mutex> myLock(_mutex);
            std::string input = _queue->receive(); // TODO: Store input in private member variables

            calculateNextMove(); // TODO: Implement
            
            std::string move = "player " + std::to_string(_id) + " has made his move."; // TODO: Replace by calculated move

            _queue->send(std::move(calculateInputForNextPlayer(move)));

            // set _playsNext to other player
            if (_id == 1) { _playsNext = 2; }
            else { _playsNext = 1; }

            _queue->print(); // TODO: Remove
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}