#ifndef CD_PLAYER_HPP
#define CD_PLAYER_HPP

#include <memory>
#include <string>
#include <iostream>

class CdPlayer;

// Base State class
class State {
public:
    virtual ~State() = default;
    virtual void power_pressed(CdPlayer* player) = 0;
    virtual void play_pause_pressed(CdPlayer* player) = 0;
    virtual void stop_pressed(CdPlayer* player) = 0;
    virtual void entry_action() = 0;
    virtual std::string get_name() const = 0;
};

// CdPlayer class
class CdPlayer {
private:
    std::unique_ptr<State> off_state;
    std::unique_ptr<State> stopped_state;
    std::unique_ptr<State> playing_state;
    std::unique_ptr<State> paused_state;
    State* current_state;

public:
    CdPlayer();
    void set_state(State* new_state);
    void power_pressed();
    void play_pause_pressed();
    void stop_pressed();
    State* get_off_state() const;
    State* get_stopped_state() const;
    State* get_playing_state() const;
    State* get_paused_state() const;
};

// Inherent from parent state - override
class OffState : public State {
public:
    std::string get_name() const override;
    void power_pressed(CdPlayer* player) override;
    void play_pause_pressed(CdPlayer* player) override;
    void stop_pressed(CdPlayer* player) override;
    void entry_action() override;
};

class StoppedState : public State {
public:
    std::string get_name() const override;
    void power_pressed(CdPlayer* player) override;
    void play_pause_pressed(CdPlayer* player) override;
    void stop_pressed(CdPlayer* player) override;
    void entry_action() override;
};

class PlayingState : public State {
public:
    std::string get_name() const override;
    void power_pressed(CdPlayer* player) override;
    void play_pause_pressed(CdPlayer* player) override;
    void stop_pressed(CdPlayer* player) override;
    void entry_action() override;
};

class PausedState : public State {
public:
    std::string get_name() const override;
    void power_pressed(CdPlayer* player) override;
    void play_pause_pressed(CdPlayer* player) override;
    void stop_pressed(CdPlayer* player) override;
    void entry_action() override;
};

#endif // CD_PLAYER_HPP