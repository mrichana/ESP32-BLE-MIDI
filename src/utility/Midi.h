#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>
#include "Debug.h"


class Midi {
public:
    void noteOn(uint8_t channel, uint8_t note, uint8_t velocity);
    void noteOff(uint8_t channel, uint8_t note, uint8_t velocity);
    void controlChange(uint8_t channel, uint8_t controller, uint8_t value);
    void programChange(uint8_t channel, uint8_t program);
    void pitchBend(uint8_t channel, uint8_t lsb, uint8_t msb);
    /**
     * @param channel Midi channel
     * @param value Pitch bend value, from 0 to 16383
     * */
    void pitchBend(uint8_t channel, uint16_t value);
    /**
     * This function is useful if you do not want to calculate lsb and msb of the pitchbend value yourself.
     * @param channel Midi channel
     * @param semitones Number of semitones, from -range to +range (pitchbend values outside of range will be ignored)
     * @param range Range of the pitch bend in semitones (default value is 4, which is -2 to +2 semitones)
     * */
    void pitchBend(uint8_t channel, float semitones, float range = 4);

    void setNoteOnCallback(void (*callback)(uint16_t timestamp, uint8_t channel, uint8_t note, uint8_t velocity));
    void setNoteOffCallback(void (*callback)(uint16_t timestamp, uint8_t channel, uint8_t note, uint8_t velocity));
    void setAfterTouchPolyCallback(void (*callback)(uint16_t timestamp, uint8_t channel, uint8_t note, uint8_t pressure));
    void setControlChangeCallback(void (*callback)(uint16_t timestamp, uint8_t channel, uint8_t controller, uint8_t value));
    void setProgramChangeCallback(void (*callback)(uint16_t timestamp, uint8_t channel, uint8_t program));
    void setAfterTouchCallback(void (*callback)(uint16_t timestamp, uint8_t channel, uint8_t pressure));
    void setPitchBendCallback(void (*callback)(uint16_t timestamp, uint8_t channel, uint8_t lsb, uint8_t msb));
    void setPitchBendCallback(void (*callback)(uint16_t timestamp, uint8_t channel, uint16_t value));

    void enableDebugging(Stream& debugStream = Serial);
    void disableDebugging();

protected:
    virtual void sendPacket(uint8_t *packet, uint8_t packetSize) = 0;
    void receivePacket(uint8_t *packet, uint8_t packetSize);
    Debug debug;

private:
    void sendMessage(uint8_t *message, uint8_t messageSize);
    void (*noteOnCallback)(uint16_t, uint8_t, uint8_t, uint8_t) = nullptr;
    void (*noteOffCallback)(uint16_t, uint8_t, uint8_t, uint8_t) = nullptr;
    void (*afterTouchPolyCallback)(uint16_t, uint8_t, uint8_t, uint8_t) = nullptr;
    void (*controlChangeCallback)(uint16_t, uint8_t, uint8_t, uint8_t) = nullptr;
    void (*programChangeCallback)(uint16_t, uint8_t, uint8_t) = nullptr;
    void (*afterTouchCallback)(uint16_t, uint8_t, uint8_t) = nullptr;
    void (*pitchBendCallback)(uint16_t, uint8_t, uint8_t, uint8_t) = nullptr;
    void (*pitchBendCallback2)(uint16_t, uint8_t, uint16_t) = nullptr;

    uint16_t currentTimestamp = 0;
    
};

#endif