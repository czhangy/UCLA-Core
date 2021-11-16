# Creative Project

## Goal

**Design, implement, and demo a creative project on the FPGA board.**

## Requirements

- Proposal
  - Explain the objective of the design
  - Specify what FPGA components will be used for input and output signals
  - Break down the design into milestones to create a rubric for the project
- Battleship
  - Two modes:
    - Placement mode
      - Players should be able to place their 5 ships (1 5x1, 1 4x1, 2 3x1s, 1 2x1) in various locations within a 10x10 grid
        - Ships cannot be placed out of bounds or overlapping another ship
        - The button pad will be used to control the position of the ships
        - The middle button of the button pad will be used to place the ship
        - The rightmost switch (`sw7`) will be used to determine the orientation of the ship
      - Player 1 will place all 5 of their ships first, followed by player 2
    - Game mode
      - Players will take turns choosing grid coordinates to fire on
        - Shots cannot be taken out of bounds
        - If a shot hits an enemy ship, the player will get another turn
        - If a shot misses, the other player's turn will begin
      - Once one player's ships are all sunk, the game will end
      - Each player's remaining ship count will be displayed on the seven-segment display
  - An asynchronous reset button that resets the entire game
  - The game board must be displayed using VGA
    - Both players have a distinct playing board
    - A win screen for both players
- Report
  - Introduction
  - Design Description
  - Simulation Documentation
  - Conclusion

## Deliverables

- [x] Proposal
  - [x] Objective
  - [x] Description of the project
  - [x] Required components
  - [x] Design milestones
  - [x] Grading rubric
- [ ] Code
  - [x] Debouncer
    - [x] The switches and buttons must be debounced, sampling them at a lower frequency than their noise
  - [x] Metastability
    - [x] The signals of the switches and buttons must be held stable when being sampled
    - [x] Accounting for the inputs' asynchronous nature
  - [x] Clock Divider
    - [x] A clock signal (`50 - 700Hz`) used to multiplex the seven-segment display
    - [x] A clock signal (`25MHz`) used to multiplex the VGA output
  - [ ] Placement mode
    - [ ] Ship placement and game board update
    - [ ] All 5 ships functional
    - [ ] Placement inputs
    - [ ] Valid placement detection
    - [ ] Player turn order established
  - [ ] Game mode
    - [ ] Firing mechanics and proper board updates
    - [ ] Valid shot detection
    - [ ] Turn mechanics
    - [ ] Game end mechanics
  - [ ] VGA display
    - [ ] Game boards
    - [ ] Win screens
  - [ ] SSD display
  - [ ] UCF file
- [ ] Report
- [ ] Submission
  - [ ] Submit a cleaned and zipped ISE project file
  - [ ] Submit an electronic copy of the report

