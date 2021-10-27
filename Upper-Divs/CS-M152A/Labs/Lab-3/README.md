# Stopwatch

## Goal

**Use the Xilinx ISE, Nexys 3 FGPA, and FSM design principles to design a stopwatch.**

## Requirements

- Stopwatch
  - A basic clock that counts minutes and seconds
  - Adjustable by two inputs:
    - `ADJ`: an input that, when set to high, sets the clock to adjustment mode, incrementing either the minutes or seconds at a rate of `2Hz`
      - During adjustment mode, the display must blink at a rate between `1Hz` and `2Hz`
    - `SEL`: an input that determines whether minutes (`0`) or seconds (`1`) are being adjusted
    - These should be bound to switches on the FGPA
  - Controlled by two other inputs:
    - `RESET`: should force all counters to the initial state `00:00`
    - `PAUSE`: should pause the counter when pressed, and then continue when pressed again
    - These should be bound to buttons on the FGPA

## Deliverables

- Coding
  - [ ] The decade counter
    - [ ] A seconds counter that increments every second
    - [ ] Every 60 seconds, the seconds counter will reach the maximum value of `59`, reset to `00`, and increment the minutes counter on the next clock cycle
  - [ ] The clock divider
    - [ ] A `2Hz` clock used in adjustment mode
    - [ ] A `1Hz` clock used to increment the counter
    - [ ] A fast clock (`50 - 700Hz`) used to multiplex the seven-segment display
    - [ ] A `> 1Hz` clock used for blinking the adjustment mode
  - [ ] Connect the counter to the seven-segment display
  - [ ] Debouncing
    - [ ] The switches and buttons must be debounced, sampling them at a lower frequency than their noise
  - [ ] Metastability
    - [ ] The signals of the switches and buttons must be held stable when being sampled
    - [ ] Accounting for the inputs' asynchronous nature
  - [ ] UCF
    - [ ] Create a UCF file for the counter
    - [ ] Implement `LOC` constraints
  - [ ] Testbench

- Demo
  - [ ] Explain the FSM design and diagram
  - [ ] Explanation of the counter
  - [ ] Explanation of the 4 clocks
  - [ ] Explanation of the button debouncing
  - [ ] Explanation of the seven-second display
  - [ ] Explanation of the testbench and simulation results

- Submission
  - [ ]  Submit a cleaned and zipped ISE project file
  - [ ]  Submit an electronic copy of the report



## Relevant Links

- **[Nexys3 Reference Manual](https://digilent.com/reference/programmable-logic/nexys-3/reference-manual)**

