#include "cd_player.hpp"

// CdPlayer implementation
CdPlayer::CdPlayer()
    : off_state(std::make_unique<OffState>()),
      stopped_state(std::make_unique<StoppedState>()),
      playing_state(std::make_unique<PlayingState>()),
      paused_state(std::make_unique<PausedState>()),
      current_state(off_state.get())
{
    current_state->entry_action();
}

// setters for base class 
void CdPlayer::set_state(State* new_state) {
    current_state = new_state;
    current_state->entry_action();
}

void CdPlayer::power_pressed() {
    current_state->power_pressed(this);
}

void CdPlayer::play_pause_pressed() {
    current_state->play_pause_pressed(this);
}

void CdPlayer::stop_pressed() {
    current_state->stop_pressed(this);
}

// getters for base class
State* CdPlayer::get_off_state() const {
    return off_state.get();
}

State* CdPlayer::get_stopped_state() const {
    return stopped_state.get();
}

State* CdPlayer::get_playing_state() const {
    return playing_state.get();
}

State* CdPlayer::get_paused_state() const {
    return paused_state.get();
}

// OffState class implementation
std::string OffState::get_name() const {
    return "Off";
}

void OffState::power_pressed(CdPlayer* player) {
    player->set_state(player->get_stopped_state());
}

void OffState::play_pause_pressed(CdPlayer*) {
    // No action
}

void OffState::stop_pressed(CdPlayer*) {
    // No action
}

void OffState::entry_action() {
    std::cout << "Device is off." << std::endl;
}

// StoppedState class implementation
std::string StoppedState::get_name() const {
    return "Stopped";
}

void StoppedState::power_pressed(CdPlayer* player) {
    player->set_state(player->get_off_state());
}

void StoppedState::play_pause_pressed(CdPlayer* player) {
    player->set_state(player->get_playing_state());
}

void StoppedState::stop_pressed(CdPlayer*) {
    std::cout << "Already stopped." << std::endl;
}

void StoppedState::entry_action() {
    std::cout << "Device is on, stopped." << std::endl;
}

// PlayingState class implementation
std::string PlayingState::get_name() const {
    return "Playing";
}

void PlayingState::power_pressed(CdPlayer* player) {
    player->set_state(player->get_off_state());
}

void PlayingState::play_pause_pressed(CdPlayer* player) {
    player->set_state(player->get_paused_state());
}

void PlayingState::stop_pressed(CdPlayer* player) {
    player->set_state(player->get_stopped_state());
}

void PlayingState::entry_action() {
    std::cout << "Playing media." << std::endl;
}

// PausedState class implementation
std::string PausedState::get_name() const {
    return "Paused";
}

void PausedState::power_pressed(CdPlayer* player) {
    player->set_state(player->get_off_state());
}

void PausedState::play_pause_pressed(CdPlayer* player) {
    player->set_state(player->get_playing_state());
}

void PausedState::stop_pressed(CdPlayer* player) {
    player->set_state(player->get_stopped_state());
}

void PausedState::entry_action() {
    std::cout << "Paused." << std::endl;
}