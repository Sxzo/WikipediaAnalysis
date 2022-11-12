#include "graph.h"

#include <catch2/catch_test_macros.hpp>
#include <set>

// Graph g = Graph("articles.tsv", "links.tsv"); Might work???
Graph g;
//Test cases for graph constructor:
TEST_CASE("Graph is not empty", "[empty]") {
    REQUIRE(g.getNodeListSize() > 0);
}

TEST_CASE("Graph contains correct amount of nodes", "[size]") {
    // Correct node count presumed to be 4604
    REQUIRE(g.getNodeListSize() == 4604);
}	

TEST_CASE("Test Related: Oil Crisis", "[related]") {

    std::set<Graph::Node*> expected;

    //adds all the expected nodes to expected:
    expected.insert(g.getNode("Algeria"));
	expected.insert(g.getNode("Arab-Israeli conflict"));
	expected.insert(g.getNode("Australia"));
	expected.insert(g.getNode("BBC"));
	expected.insert(g.getNode("Bretton Woods system"));
	expected.insert(g.getNode("Canada"));
	expected.insert(g.getNode("Chile"));
	expected.insert(g.getNode("Coal"));
	expected.insert(g.getNode("Cold War"));
	expected.insert(g.getNode("Egypt"));
	expected.insert(g.getNode("Electronics"));
	expected.insert(g.getNode("Ethanol"));
	expected.insert(g.getNode("Gold"));
	expected.insert(g.getNode("Iran"));
	expected.insert(g.getNode("Iraq"));
	expected.insert(g.getNode("Israel"));
	expected.insert(g.getNode("Kuwait"));
	expected.insert(g.getNode("Latin America"));
	expected.insert(g.getNode("Libya"));
	expected.insert(g.getNode("Market"));
	expected.insert(g.getNode("Mexico"));
	expected.insert(g.getNode("Middle East"));
	expected.insert(g.getNode("Mineral"));
	expected.insert(g.getNode("Natural gas"));
	expected.insert(g.getNode("Netherlands"));
	expected.insert(g.getNode("Newspaper"));
	expected.insert(g.getNode("Nigeria"));
	expected.insert(g.getNode("North America"));
	expected.insert(g.getNode("Nuclear power"));
	expected.insert(g.getNode("People's Republic of China"));
	expected.insert(g.getNode("Persian Gulf"));
	expected.insert(g.getNode("Petroleum"));
	expected.insert(g.getNode("Portugal"));
	expected.insert(g.getNode("Qatar"));
	expected.insert(g.getNode("Richard Nixon"));
	expected.insert(g.getNode("Russia"));
	expected.insert(g.getNode("Saudi Arabia"));
	expected.insert(g.getNode("South Africa"));
	expected.insert(g.getNode("Soviet Union"));
	expected.insert(g.getNode("Supply and demand"));
	expected.insert(g.getNode("Syria"));
	expected.insert(g.getNode("United Arab Emirates"));
	expected.insert(g.getNode("United Kingdom"));
	expected.insert(g.getNode("United Nations"));
	expected.insert(g.getNode("United States"));
	expected.insert(g.getNode("United States dollar"));
	expected.insert(g.getNode("Venezuela"));
	expected.insert(g.getNode("Wheat"));
	expected.insert(g.getNode("Wood fuel"));
	expected.insert(g.getNode("World War II"));
	expected.insert(g.getNode("Yom Kippur War"));

    std::vector<string> actual = g.incidentEdges(g.getNode("1973 oil crisis"));
    std::set<Graph::Node*> actualSet;
    
    for (size_t i = 0; i < actual.size(); i++) {
       actualSet.insert(g.getNode(actual[i]));
    }
    for (Graph::Node* node : expected) {
        REQUIRE(actualSet.find(node) != actualSet.end()); 
    }
    REQUIRE(expected.size() == actualSet.size());
}

TEST_CASE("Test Degree : small", "[degree1]") {
    // A cappella degrees should be 10
    std::vector<string> actual = g.incidentEdges(g.getNode("A cappella")); 
    REQUIRE(actual.size() == 10); 
}

TEST_CASE("Test Degree : medium", "[degree2]") {
    // ACDC Degrees should be 27 
    std::vector<string> actual = g.incidentEdges(g.getNode("AC DC"));
    REQUIRE(actual.size() == 27);   
}

TEST_CASE("Test degree : large", "[degree3]") {
    // 11th century degrees should be 46 
    std::vector<string> actual = g.incidentEdges(g.getNode("11th century"));
    REQUIRE(actual.size() == 46);
}

TEST_CASE("areAdjacent test : one", "[adj1]") {
    REQUIRE(g.areAdjacent(g.getNode("11th century"), g.getNode("Time")) == true);
    REQUIRE(g.areAdjacent(g.getNode("Time"), g.getNode("11th century")) == true);
}

TEST_CASE("areAdjacent test : two", "[adj2]") {
    REQUIRE(g.areAdjacent(g.getNode("13th century"), g.getNode("China")) == true);
    REQUIRE(g.areAdjacent(g.getNode("China"), g.getNode("13th century")) == true);
}

TEST_CASE("areAdjacent test : three", "[adj3]") {
    REQUIRE(g.areAdjacent(g.getNode("AK-47"), g.getNode("Soviet Union")) == true);
    REQUIRE(g.areAdjacent(g.getNode("Soviet Union"), g.getNode("AK-47")) == true);
}

TEST_CASE("Test Related: 1896 Summer Olympics", "[related]") {

    std::set<Graph::Node*> expected;

    //adds all the expected nodes to expected:
    expected.insert(g.getNode("Athens"));
	expected.insert(g.getNode("Athletics (track and field)")); //Athletics (track and field)
	expected.insert(g.getNode("Australia"));
	expected.insert(g.getNode("Austria"));
	expected.insert(g.getNode("British Empire"));
	expected.insert(g.getNode("Christianity"));
	expected.insert(g.getNode("Cricket"));
	expected.insert(g.getNode("Cyprus"));
	expected.insert(g.getNode("Eastern Orthodox Church War"));
	expected.insert(g.getNode("Egypt"));
	expected.insert(g.getNode("Europe"));
	expected.insert(g.getNode("Football (soccer)")); //Football (soccer)
	expected.insert(g.getNode("France"));
	expected.insert(g.getNode("Germany"));
	expected.insert(g.getNode("Greece"));
	expected.insert(g.getNode("Greek War of Independence"));
	expected.insert(g.getNode("Hungary"));
	expected.insert(g.getNode("London"));
	expected.insert(g.getNode("Olympic Games"));
	expected.insert(g.getNode("Market"));
	expected.insert(g.getNode("Paris"));
	expected.insert(g.getNode("Roman Catholic Church"));
	expected.insert(g.getNode("Roman Empire"));
	expected.insert(g.getNode("Serbia"));
	expected.insert(g.getNode("Slovakia"));
	expected.insert(g.getNode("Sport"));
	expected.insert(g.getNode("Switzerland"));
	expected.insert(g.getNode("United States"));

    std::vector<string> actual = g.incidentEdges(g.getNode("1973 oil crisis"));
    std::set<Graph::Node*> actualSet;
    
    for (size_t i = 0; i < actual.size(); i++) {
       actualSet.insert(g.getNode(actual[i]));
    }
    for (Graph::Node* node : expected) {
        REQUIRE(actualSet.find(node) != actualSet.end()); 
    }
    REQUIRE(expected.size() == actualSet.size());
}

TEST_CASE("Test Related: 1997 Pacific hurricane season", "[related]") {

    std::set<Graph::Node*> expected;

    //adds all the expected nodes to expected:
    expected.insert(g.getNode("California"));
	expected.insert(g.getNode("Caribbean Sea")); 
	expected.insert(g.getNode("El Niño-Southern Oscillation")); //El Niño-Southern Oscillation
	expected.insert(g.getNode("El Salvador"));
	expected.insert(g.getNode("Guam"));
	expected.insert(g.getNode("Japan"));
	expected.insert(g.getNode("Johnston Atoll"));
	expected.insert(g.getNode("Meteorology"));
	expected.insert(g.getNode("Mexico"));
	expected.insert(g.getNode("Nicaragua"));
	expected.insert(g.getNode("Pacific Ocean"));
	expected.insert(g.getNode("Palmyra Atoll")); 
	expected.insert(g.getNode("Tropical cyclone"));
	expected.insert(g.getNode("U.S. state"));
	expected.insert(g.getNode("United States"));
	expected.insert(g.getNode("Wake Island"));

    std::vector<string> actual = g.incidentEdges(g.getNode("1973 oil crisis"));
    std::set<Graph::Node*> actualSet;
    
    for (size_t i = 0; i < actual.size(); i++) {
       actualSet.insert(g.getNode(actual[i]));
    }
    for (Graph::Node* node : expected) {
        REQUIRE(actualSet.find(node) != actualSet.end()); 
    }
    REQUIRE(expected.size() == actualSet.size());
}




// Test cases for BFS

// Test cases for Dijkstra

// Stoer-Wagner tests
