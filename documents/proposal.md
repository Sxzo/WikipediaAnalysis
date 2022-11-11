## Leading Question 

The purpose of our project is to examine the interconnection between Wikipedia articles via hyperlinks. We can use Dijkstra’s algorithm to find the path that traverses through articles with the smallest amount of links, Stoer-Wagner algorithm to find which hyperlinks we would have to remove in order for two articles to not be connected, and a BFS to create a visualization of the hyperlink network.

## Dataset Acquisition

### Data Format
Data Format: We are getting out dataset from the website http://snap.stanford.edu/data/wikispeedia.html which was recommended on the course-given google document. The input file downloaded from the actual website is in the form of “.tar.gz” which we will then unzip into several .tar files. Out of these files, we will use two, one with the list of articles, and another with the list of links within articles. These files have a total file size of 3 mb and we intend to use all of the data contained within them.
### Data Correction
We will parse our input data line by line and add the article name on each line to our node list while adding all the hyperlinks to our edge adjacency list. After this, we can check each edge in the adjacency list to ensure that there is a corresponding node in the node list. In instances where we uncover an error, we will accordingly make removals from the edge list. This can be done with an error-checker function that we will create and run locally before using the data for our project. 

### Data Storage
We will be using a graph to store articles as nodes and the hyperlinks between articles as edges. We will use a list for the nodes and will use an adjacency list to store the edges. The weight of the edges will be the sum of the total number of hyperlinks on each node. We expect the total storage costs of our dataset to be O(n+m), where n is the number of articles and m is the number of hyperlinks. 	
## Algorithm 

### Function Inputs
Our BFS traversal for visualizing the graph will take in a starting node. Our Dijkstra’s algorithm will take in a starting node and an ending node. Our Stoer-Wagner algorithm will take our graph object and two nodes as its parameters. At this point in using the algorithm, we will have already constructed the graph object based on the dataset in our constructor. This will make it easy to pull nodes from the node list when needed. 
### Function Outputs
For our shortest path query, our function will output a string-formatted path taken with a corresponding integer that represents its length, as well as an integer that represents the total number of links seen on the path to the destination. In our cut-edge function, we will return the hyperlinks that would need to be invalid in order for certain articles to become inaccessible. Finally, our visualization component of the paths using BFS would be outputted as a PNG or animated GIF.
### Function Time Complexity
We will implement the traversal in O(m + n) time, Djikstra's algorithm in O(nlogn + mlogn) time, and Stoer-Wagner in O($n^3)$ time. All three will use O(n + m) memory.
## Timeline
Weekly Check-ins: Every Friday of the week

Complete Data Parsing Algorithm and tests: November 10th

Complete Graph Construct – populate node list and edge adjacency List:  November 10th

Complete BFS Visualization and Tests: December 3rd

Complete Dijkstra Algorithm and Tests: November 17th

Complete Stoer-Wagner and Tests: November 24th

Read.Me: December 5th

Written Report: December 5th

Presentation: December 5th

