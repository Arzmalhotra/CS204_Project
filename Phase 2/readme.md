Below is a concise README formatted for GitHub:

---

# Machine Code Simulator and GUI

A simple project that simulates a processor executing machine code (e.g., a factorial function) and displays the results. The C++ simulator reads instructions from a file, processes them, and writes the final register and memory states to an output file. A Python GUI built with Tkinter enables quick compilation and execution of the simulator with a user-friendly interface.

## Features

- **C++ Simulator (`phase2.cpp`):**
  - Reads machine instructions from `machine_code.mc`
  - Simulates instruction processing (fetch–decode–execute cycle)
  - Writes register and memory states to `data_out.mem`
  - Tracks clock cycles during execution

- **Python GUI (`phase_2_gui.py`):**
  - Provides an input area to edit instructions
  - Compiles and runs the C++ simulator using `g++`
  - Displays compilation and execution outputs in a text widget

## Quick Start

1. **C++ Simulator:**
   - Compile:  
     ```bash
     g++ phase2.cpp -o simulator
     ```
   - Run:  
     ```bash
     ./simulator
     ```
   - Check `data_out.mem` for results.

2. **Python GUI:**
   - Run:  
     ```bash
     python3 phase_2_gui.py
     ```
   - Use the interface to save instruction inputs and compile/run the simulator.

## Requirements

- **C++ Simulator:** A C++ compiler (e.g., `g++`)
- **Python GUI:** Python 3.x with Tkinter

---

Feel free to adjust any details as necessary for your repository.
