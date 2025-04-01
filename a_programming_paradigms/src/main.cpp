#include "cd_player.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << "Media Player Simulator" << std::endl;
    std::cout << "Commands: power, play_pause, stop, quit" << std::endl;

    CdPlayer player;

    std::string input;
    // Read input and continue looping until "quit" is entered. Would use enum but Im not confident in my c++
    std::cout << "Please enter command: ";
    while (std::getline(std::cin, input) && input != "quit") {
        if (input == "power") {
            player.power_pressed();
        } else if (input == "play_pause") {
            player.play_pause_pressed();
        } else if (input == "stop") {
            player.stop_pressed();
        } else {
            std::cout << "Invalid input" << std::endl;
        }
        // Get user input.
        std::cout << "Please enter input: ";
    }

    return 0;
}
