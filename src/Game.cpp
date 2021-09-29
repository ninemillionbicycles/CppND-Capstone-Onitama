#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>

#include "Player.h"

int main() {
    // create monitor object as a shared pointer to enable access by multiple threads
    // queue will be used to pass a string that contains the input for each turn
    std::shared_ptr<MessageQueue<std::string>> queue(new MessageQueue<std::string>); 

    int playsNext = 1; // player 1 starts playing first

    // create two players
    Player player1 = Player(1, queue, playsNext);
    Player player2 = Player(2, queue, playsNext);

    // Fill the queue with something to get the game started. TODO: Replace with actual input for player 1
    queue->send("Game started ...");
    queue->print(); // TODO: Remove

    // start their play() functions as std::async
    std::vector<std::future<void>> futures;

    futures.emplace_back(std::async(std::launch::async, &Player::play, &player1));
    futures.emplace_back(std::async(std::launch::async, &Player::play, &player2));

    // wait for the results to avoid premature termination of main()
    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) { ftr.wait(); });

    // TODO: print result of which player has won

    return 0;
}