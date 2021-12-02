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
      - Players should be able to place their 3x1 ships in various locations within a 5x5 grid
        - Ships cannot be placed out of bounds or overlapping another ship
        - Switches will encode the coordinates of the ship in binary
        - The middle button of the button pad will be used to place the ship
        - The top button will be used to toggle the orientation of the ship
      - Player 1 will place all of their ships first, followed by player 2
    - Game mode
      - Players will take turns choosing grid coordinates to fire on
        - Shots cannot be taken out of bounds
        - If a shot hits an enemy ship, the player will get another turn
        - If a shot misses, the other player's turn will begin
      - Once one player's ships are all sunk, the game will end
  - An asynchronous reset button that resets the entire game
  - The seven-segment display displays the current player
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
- [x] Code
  - [x] Debouncer
    - [x] The switches and buttons must be debounced, sampling them at a lower frequency than their noise
  - [x] Metastability
    - [x] The signals of the switches and buttons must be held stable when being sampled
    - [x] Accounting for the inputs' asynchronous nature
  - [x] Clock Divider
    - [x] A clock signal (`50 - 700Hz`) used to multiplex the seven-segment display
    - [x] A clock signal (`25MHz`) used to multiplex the VGA output
  - [x] Placement mode
    - [x] Ship placement and game board update
    - [x] All 6 ships functional
    - [x] Placement inputs
    - [x] Valid placement detection
    - [x] Player turn order established
  - [x] Game mode
    - [x] Firing mechanics and proper board updates
    - [x] Valid shot detection
    - [x] Turn mechanics
    - [x] Game end mechanics
  - [x] VGA display
    - [x] Game boards
    - [x] Win screens
  - [x] SSD display
  - [x] UCF file
- [ ] Report
- [ ] Submission
  - [x] Submit a cleaned and zipped ISE project file
  - [ ] Submit an electronic copy of the report

