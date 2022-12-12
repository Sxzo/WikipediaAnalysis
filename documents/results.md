# Just How Connected Are Wikipedia Articles? 

###### Lev, Joseph T, Joseph M, Siddhant

> ### Our Three Primary Aglorithms for Analysis: 

## Dijkstras

Dijkstras algorithm is a simple shortest path algorithm that we used to examine optimal distances between articles. Ultimately, we created two functions for the purpose of our analysis. One returned an integer representing the shortest path weight and the other returned a vector containing the path actually traversed between the two nodes. For the purpose of our work, the latter function (returning a vector), proved to be of far more sustinence, although the conclusions of both were ultimately transitively explanatory of each other as illustrated in the conclusion. 

*Minimum Links Traversed*

This used the int function of dijkstras and was helpful in explaining the sheer level of connectivity throughout the nodes of the graph. For example, a short traversal from an article title `Viking` to one titled `Glass` encountered a staggering **181 links** on its path of only 4 nodes. 

<sub>Pseudocode for links encountered</sub>

`cout << graph.dijkstras("Viking", "Glass") << endl ` 
> 181

`cout << graph.dijkstras("Zulu", "Global city") << endl` 
> 261
 
`cout << graph.dijkstras("Heron", "Humour") << endl` 
> 82

*Shortest Node Path*

This used the vector function of dijkstras and was remarkable for understanding just how easy it was to connect any article in the graph. We hypothesized needing large traversals of 20+ nodes to connect seemingly unrelated topics but our findings put connectivity distance into a new astounding perspective. We found that we were able to connect (arbitrarily) unrelated articles with a path of no greater than **5 nodes**. 


<sub>Pseudocode for nodes traversed</sub>

`cout << graph.dijkstrasVector("Viking", "Glass").size << endl ` 
> 4

`cout << graph.dijkstrasVector("Zulu", "Global city").size << endl` 
> 3
 
`cout << graph.dijkstrasVector("Heron", "Humour").size << endl` 
> 4

## Stoer-Wagner

Our primary idea behind utilizing Stoer-Wagner in our analysis was to be able to find to minimum cut edges that could potentially illustrate the most signifigant links in the entire graph. We hoped that this finding would allude to especially important articles that played a massive role in connecting a vast number of other articles. 

*Our shortcoming:*

We fell short of achieving our goal in using this algorithm on our dataset due to a simple oversight in its actual runtime. Our implementation of Stoer-Wagner's minimum cut algorithm has a runtime of **O(|V|^3)**, which isn't a daunting runtime on a graph of around 100 nodes persay. However, our graph's primary connected component contains over 4000 nodes, which means that Stoer-Wagner would have taken over **64,000,000,000** *(64 billion!)* iterations to complete. Our virtual machine was simply not cut out for this task, and as a result, we felt short of actually being able to use it in the work of our analysis. 

## Breadth First Search

We used BFS as a means to understand underlying connectivity by measuring the size of the graph's components. It didn't play a role in helping us see how individual pages connected to others, but rather, served as a tool to see the span of connections starting from any one specific article. Our results were substantial, and we found that of the 4604 nodes in our dataset, **4588** were found to be in a single connected component. 

`cout << graph.bfs("Viking").size << endl` 
> 4588 

`cout << graph.bfs("Directdebit").size << endl`
> 3

***

## In Conclusion

Ultimately, our leading question can be answered in a very succinct manner:

> Just How Connected Are Wikipedia Articles? 
**Extremely connected.**

Our most substantive proof of this is found from the usage of BFS in measuring the size of connected components. When it's taken into account that a staggering **99.65%** percent of nodes can be found in one component, it becomes clear that these articles are almost all connected in some form or another. The articles that lie in the remaining 0.35% are ones that either have no links contained within them at all or link to articles that are extremely specific and don't have any branches (i.e `Directdebit`). Alongside BFS, Dijkstra's path finding algorithm helped us see that these articles were not connected by an overwhelmingly large distance, despite the size of their components. As described above, we found that we could connect any two articles (within a component) by going through no more than **5 links**. This is especially remarkable when considering just how unrelated some of these articles are in nature. 

***

## Visualization

###### "No graphics library? No problem."

Although our leading question was answered by using the three algorithms described above, we wanted to go above and beyond simply pooling together data, and decided to illustrate some of our findings. 

Here's what the degree of `South America` looks like:

![alt text](https://github.com/joetamulaitis/cryptic/blob/main/documents/South%20America%20Degree.gif "South America Degree")

Note that the radius of each drawn node is based off its degree. 

![alt text](https://github.com/joetamulaitis/cryptic/blob/main/documents/South%20America%20Degree.png "South America Degree")

***

Here's an image that'll put the size of `4604 nodes` into perspective:

![alt text](https://github.com/joetamulaitis/cryptic/blob/main/documents/Node%20Base.png "Node Base")

***

This is what the traversal of the first `100 nodes` of BFS starting on `Zulu` looks like: 

![alt text](https://github.com/joetamulaitis/cryptic/blob/main/documents/BFS%20Zulu.gif "Zulu Animation")
![alt text](https://github.com/joetamulaitis/cryptic/blob/main/documents/BFS%20Zulu.png "Zulu PNG")

And this is what the traversal looks like on the mere `3 nodes` found in the component of `Directdebit`:

![alt text](https://github.com/joetamulaitis/cryptic/blob/main/documents/BFS%20Directdebit.gif "Directdebit animation")

*** 

Finally, this is what it looks like to take the shortest path from `Viking` to `Glass`:

![alt text](https://github.com/joetamulaitis/cryptic/blob/main/documents/Dijkstras%20Path%20from%20Viking%20to%20Glass.gif "Dijkstras animation")

***

###### We hope that you enjoyed reading about this project just as much as we enjoyed making it. 

> All credit goes to http://snap.stanford.edu/data/ for our dataset.






