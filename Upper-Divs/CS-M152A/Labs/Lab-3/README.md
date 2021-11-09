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
  - [x] The decade counter
    - [x] A seconds counter that increments every second
    - [x] Every 60 seconds, the seconds counter will reach the maximum value of `59`, reset to `00`, and increment the minutes counter on the next clock cycle
  - [x] The clock divider
    - [x] A `2Hz` clock used in adjustment mode
    - [x] A `1Hz` clock used to increment the counter
    - [x] A fast clock (`50 - 700Hz`) used to multiplex the seven-segment display
    - [x] A `> 1Hz` clock used for blinking the adjustment mode
  - [x] Connect the counter to the seven-segment display
  - [x] Debouncer
    - [x] The switches and buttons must be debounced, sampling them at a lower frequency than their noise
  - [x] Metastability
    - [x] The signals of the switches and buttons must be held stable when being sampled
    - [x] Accounting for the inputs' asynchronous nature
  - [x] UCF
    - [x] Create a UCF file for the counter
  - [x] Testbench
    - [x] Test normal mode
    - [x] Test minute adjustment mode
    - [x] Test second adjustment mode
    - [x] Test normal mode after adjustment mode
    - [x] Test pause
    - [x] Test reset
  
- Demo
  - [x] Explain the FSM design and diagram
  - [x] Explanation of the counter
  - [x] Explanation of the 4 clocks
  - [x] Explanation of the button debouncing
  - [x] Explanation of the seven-second display
  - [x] Explanation of the testbench and simulation results
  - [x] Demo on the Nexys 3 board
  
- Submission
  - [x]  Submit a cleaned and zipped ISE project file
  - [x]  Submit an electronic copy of the report



## Relevant Links

- **[Nexys3 Reference Manual](https://digilent.com/reference/programmable-logic/nexys-3/reference-manual)**

