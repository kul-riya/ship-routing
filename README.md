# Ship Routing Application (A* Pathfinding with ncurses)

This is a terminal-based ship routing application that uses **ncurses** for output and implements the **A* (A-star) algorithm** for pathfinding. The application processes real-world data with **3440 records** from an Indian government dataset.

## Features
- **A* Algorithm Implementation**: Efficient route calculation.
- **ncurses-Based Visualization**: Display results in a terminal UI.
- **Real-World Data**: Uses official government records for accurate pathfinding.
- **Pointer Diagram**: A detailed PNG file is provided for understanding the pointer structure used in the project.

## Prerequisites
Ensure the following dependencies are installed:

- **GCC Compiler**
- **ncurses Library**

On Ubuntu/Debian, install ncurses with:
```sh
sudo apt-get install libncurses-dev

For macOS (with Homebrew):
```sh
brew install ncurses

For Windows, use Cygwin or WSL with the required packages.

## Installation & Compilation

1. Clone this repository

```sh
git clone <repo-url>
cd <repo-folder>

2. Compile the source files

```sh
gcc -c main.c src/base_edges.c src/a_star.c src/graph.c src/visualization.c

3. Link object files and create executable

```sh
gcc *.o -o a.out -lncurses

4. Running the Application

Execute the compiled binary:

```sh
./a.out lat1 long1 lat2 long2
--> Constraints
starting Latitude 4.0 N
ending Latitude 25.0 N
starting Longitude 68.0E
ending Longitude 89.0E

## Dataset Information

The application processes 3440 real-world records from an Indian government dataset.

The dataset consists of geographic coordinates representing navigational points.

## File Structure

📦 ShipRoutingProject
├── 📂 src
│   ├── base_functions.c
│   ├── a_star.c
│   ├── edges.c
├── 📂 include
│   ├── base_functions.h
│   ├── a_star.h
├── main.c
├── README.md
└── pointer_diagram.png

## Contributions

Contributions are welcome! Feel free to fork the repository and submit a pull request.

## License

This project is licensed under the MIT License. See LICENSE for details.
