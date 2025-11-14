🚶‍♂️ IIT Jodhpur Campus Route Planner

A C++ project that finds the shortest walking paths between locations at IIT Jodhpur using graph algorithms like Dijkstra's and BFS.

📂 Project Structure & File Workflow

1.src/main.cpp: Runs the main user menu (CLI) and handles all user input.

2.src/graph.hpp / graph.cpp: Defines the core graph data structure (Adjacency List) to represent the campus map.

3.src/dijkstra.hpp / dijkstra.cpp: Implements the pathfinding algorithms (Dijkstra's, BFS) and connectivity checks.

4.src/io.hpp / io.cpp: Contains functions to read and parse the campus_map.txt file.

5.data/campus_map.txt: The input data file that defines all locations (nodes) and roads/paths (edges) with their distances.

🧪 How to Compile & Run

1. Build Command

Open your terminal and run the following g++ command from the project's root directory:
g++ src/*.cpp -o campus_planner -std=c++17


2. Run the Program

After building, run the compiled executable:
./campus_planner


This will start the interactive menu in your terminal.
