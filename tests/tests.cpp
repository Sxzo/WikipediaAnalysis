#include "graph.h"

using namespace cs225;


// Graph g = Graph("articles.tsv", "links.tsv"); Might work???

//Test cases for graph constructor:
TEST_CASE("Graph is not empty", "[empty]") {
    Graph g = Graph("articles.tsv", "links.tsv"); 
    REQUIRE(g.nodeList_.size() > 0);
}

TEST_CASE("Graph contains correct amount of nodes", "[size]") {
    // Correct node count presumed to be 4603
    Graph g = Graph("articles.tsv", "links.tsv");
    REQUIRE(g.nodeList_.size() == 4603);
}	

TEST_CASE("Test Related: Oil Crisis", "[related]") {
    Graph g = Graph("articles.tsv", "links.tsv");
    std::set<Node> expected;

    //adds all the expected nodes to expected:
    expected.insert(Node("Algeria"));
	expected.insert(Node("Arab-Israeli_conflict"));
	expected.insert(Node("Australia"));
	expected.insert(Node("BBC"));
	expected.insert(Node("Bretton_Woods_system"));
	expected.insert(Node("Canada"));
	expected.insert(Node("Chile"));
	expected.insert(Node("Coal"));
	expected.insert(Node("Cold_War"));
	expected.insert(Node("Egypt"));
	expected.insert(Node("Electronics"));
	expected.insert(Node("Ethanol"));
	expected.insert(Node("Gold"));
	expected.insert(Node("Iran"));
	expected.insert(Node("Iraq"));
	expected.insert(Node("Israel"));
	expected.insert(Node("Kuwait"));
	expected.insert(Node("Latin_America"));
	expected.insert(Node("Libya"));
	expected.insert(Node("Market"));
	expected.insert(Node("Mexico"));
	expected.insert(Node("Middle_East"));
	expected.insert(Node("Mineral"));
	expected.insert(Node("Natural_gas"));
	expected.insert(Node("Netherlands"));
	expected.insert(Node("Newspaper"));
	expected.insert(Node("Nigeria"));
	expected.insert(Node("North_America"));
	expected.insert(Node("Nuclear_power"));
	expected.insert(Node("People's_Republic_of_China"));
	expected.insert(Node("Persian_Gulf"));
	expected.insert(Node("Petroleum"));
	expected.insert(Node("Portugal"));
	expected.insert(Node("Qatar"));
	expected.insert(Node("Richard_Nixon"));
	expected.insert(Node("Russia"));
	expected.insert(Node("Saudi_Arabia"));
	expected.insert(Node("South_Africa"));
	expected.insert(Node("Soviet_Union"));
	expected.insert(Node("Supply_and_demand"));
	expected.insert(Node("Syria"));
	expected.insert(Node("United_Arab_Emirates"));
	expected.insert(Node("United_Kingdom"));
	expected.insert(Node("United_Nations"));
	expected.insert(Node("United_States"));
	expected.insert(Node("United_States_dollar"));
	expected.insert(Node("Venezuela"));
	expected.insert(Node("Wheat"));
	expected.insert(Node("Wood_fuel"));
	expected.insert(Node("World_War_II"));
	expected.insert(Node("Yom_Kippur_War"));

    std::vector<pair<int, Node>> actual = incidentEdges(Node("1973_oil_crisis"));
    std::set<Node> actualSet;
    
    for (size_t i = 0; i < actual.size(); i++) {
       actualSet.insert(actual.second);
    }
    for (Node node : expected) {
        REQUIRE(actualSet.contains(node)); 
    }
    REQUIRE(expected.size() == actualSet.size());
}

TEST_CASE("Test Degree : small", "[degree1]") {
    // A cappella degrees should be 10
    Graph g = Graph("articles.tsv", "links.tsv");
    std::vector<pair<int, Node>> actual = incidentEdges(Node("A_cappella")); 
    REQUIRE(actual.size() == 10); 
}

TEST_CASE("Test Degree : medium", "[degree2]") {
    // ACDC Degrees should be 27 
    Graph g = Graph("articles.tsv", "links.tsv");
    std::vector<pair<int, Node>> actual = incidentEdges(Node("AC_DC"));
    REQUIRE(actual.size() == 27);   
}

TEST_CASE("Test degree : large", "[degree3]") {
    // 11th century degrees should be 46 
    Graph g = Graph("articles.tsv", "links.tsv"); 
    std::vector<pair<int, Node>> actual incidentEdges(Node("11th_century"));
    REQUIRE(actual.size() == 46);
}

TEST_CASE("areAdjacent test : one", "[adj1]") {
    Graph g = Graph("articles.tsv", "links.tsv");
    REQUIRE(areAdjacent(Node("11th_century"), Node("Time")) == true);
    REQUIRE(areAdjacent(Node("Time"), Node("11th_century")) == true);
}

TEST_CASE("areAdjacent test : two", "[adj2]") {
    Graph g = Graph("articles.tsv", "links.tsv");
    REQUIRE(areAdjacent(Node("13th_century"), Node("China")) == true);
    REQUIRE(areAdjacent(Node("China"), Node("13th_century")) == true);
}

TEST_CASE("areAdjacent test : three", "[adj3]") {
    Graph g = Graph("articles.tsv", "links.tsv");
    REQUIRE(areAdjacent(Node("AK-47"), Node("Soviet_Union")) == true);
    REQUIRE(areAdjacent(Node("Soviet_Union"), Node("AK-47")) == true);
}

TEST_CASE("Test Related: 1896_Summer_Olympics", "[related]") {
    Graph g = Graph("articles.tsv", "links.tsv");
    std::set<Node> expected;

    //adds all the expected nodes to expected:
    expected.insert(Node("Athens"));
	expected.insert(Node("Athletics_%28track_and_field%29")); //Athletics_%28track_and_field%29
	expected.insert(Node("Australia"));
	expected.insert(Node("Austria"));
	expected.insert(Node("British_Empire"));
	expected.insert(Node("Christianity"));
	expected.insert(Node("Cricket"));
	expected.insert(Node("Cyprus"));
	expected.insert(Node("Eastern_Orthodox_Church_War"));
	expected.insert(Node("Egypt"));
	expected.insert(Node("Europe"));
	expected.insert(Node("Football_%28soccer%29")); //Football_%28soccer%29
	expected.insert(Node("France"));
	expected.insert(Node("Germany"));
	expected.insert(Node("Greece"));
	expected.insert(Node("Greek_War_of_Independence"));
	expected.insert(Node("Hungary"));
	expected.insert(Node("London"));
	expected.insert(Node("Olympic_Games"));
	expected.insert(Node("Market"));
	expected.insert(Node("Paris"));
	expected.insert(Node("Roman_Catholic_Church"));
	expected.insert(Node("Roman_Empire"));
	expected.insert(Node("Serbia"));
	expected.insert(Node("Slovakia"));
	expected.insert(Node("Sport"));
	expected.insert(Node("Switzerland"));
	expected.insert(Node("United_States"));

    std::vector<pair<int, Node>> actual = incidentEdges(Node("1973_oil_crisis"));
    std::set<Node> actualSet;
    
    for (size_t i = 0; i < actual.size(); i++) {
       actualSet.insert(actual.second);
    }
    for (Node node : expected) {
        REQUIRE(actualSet.contains(node)); 
    }
    REQUIRE(expected.size() == actualSet.size());
}

TEST_CASE("Test Related: 1997_Pacific_hurricane_season", "[related]") {
    Graph g = Graph("articles.tsv", "links.tsv");
    std::set<Node> expected;

    //adds all the expected nodes to expected:
    expected.insert(Node("California"));
	expected.insert(Node("Caribbean_Sea")); 
	expected.insert(Node("El_Ni%C3%B1o-Southern_Oscillation")); //El_Ni%C3%B1o-Southern_Oscillation
	expected.insert(Node("El_Salvador"));
	expected.insert(Node("Guam"));
	expected.insert(Node("Japan"));
	expected.insert(Node("Johnston_Atoll"));
	expected.insert(Node("Meteorology"));
	expected.insert(Node("Mexico"));
	expected.insert(Node("Nicaragua"));
	expected.insert(Node("Pacific_Ocean"));
	expected.insert(Node("Palmyra_Atoll")); 
	expected.insert(Node("Tropical_cyclone"));
	expected.insert(Node("U.S._state"));
	expected.insert(Node("United_States"));
	expected.insert(Node("Wake_Island"));

    std::vector<pair<int, Node>> actual = incidentEdges(Node("1973_oil_crisis"));
    std::set<Node> actualSet;
    
    for (size_t i = 0; i < actual.size(); i++) {
       actualSet.insert(actual.second);
    }
    for (Node node : expected) {
        REQUIRE(actualSet.contains(node)); 
    }
    REQUIRE(expected.size() == actualSet.size());
}




// Test cases for BFS

// Test cases for Dijkstra

// Stoer-Wagner tests
