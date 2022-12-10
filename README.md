# Cryptic CS 225 Final Project

## Repository Structure

Our data comes from http://snap.stanford.edu/data/wikispeedia.html. It is a set of links between Wikipedia articles that were used by people in the game Wikispeedia. The files are 'links.tsv' and 'articles.tsv' in the '/data' folder.

Our project documents, including the log, team contract, and project proposal, are found in the '/documents' folder.

The library that we used to create the PNG/GIF for our visualization is found in the '/lib' folder.

Our tests are found in the '/tests' folder.

Our graph and algorithm implementations are found in the '/src' folder.

Our 'main.cpp' file that is the entrypoint into the program is found in the '/entry' folder.

## Running instructions

The first thing that you need to do is 'cd build' in the terminal, and type 'cmake ..'.

### Main
To run the main function, type 'make main' and then './main'. From there, follow the directions given in the terminal.

### Tests
To run our tests, type 'make test', and then './test'.