# Sorting Algorithm Benchmarking

I tested the performance of 4 algorithms: 
- Selection Sort (n^2)
- Insertion Sort (n^2)
- Heap Sort (nlogn)
- Merge Sort (nlogn)

For each test, I generated a list of random integers of size:
- 10
- 100
- 1,000
- 10,000
- 100,000

With each algorithm being given an identical list.

Each sorting algorithm was given the same original list for each list size so that the comparison was fair. I measured the runtime of each algorithm in seconds and ran 3 trials. 

## Results

#### Trial 1:
| List Size | Selection Sort (s) | Insertion Sort (s) | Heap Sort (S) | Merge Sort (s) |
|---:|---:|---:|---:|---:|
| 10      | 0.00000050  | 0.000000291 | 0.000000584 | 0.00000550  |
| 100     | 0.000014959 | 0.000008584 | 0.000008166 | 0.000063666 |
| 1,000   | 0.00113925  | 0.000805875 | 0.000118292 | 0.000663167 |
| 10,000  | 0.109634    | 0.0742518   | 0.00155092  | 0.00846133  |
| 100,000 | 10.8675     | 6.97015     | 0.019961    | 0.0939702   |

#### Trial 2:
| List Size | Selection Sort (s) | Insertion Sort (s) | Heap Sort (s) | Merge Sort (s) |
|---:|---:|---:|---:|---:|
| 10      | 0.000000709 | 0.000000416 | 0.000000709 | 0.000006958 |
| 100     | 0.000019500 | 0.000010959 | 0.000010208 | 0.000084292 |
| 1,000   | 0.001290710 | 0.000777292 | 0.000118584 | 0.000686375 |
| 10,000  | 0.110207    | 0.0698674   | 0.00151717  | 0.00853512  |
| 100,000 | 11.1139     | 7.04359     | 0.0226158   | 0.101982    |

#### Trial 3
| List Size | Selection Sort (s) | Insertion Sort (s) | Heap Sort (s) | Merge Sort (s) |
|---:|---:|---:|---:|---:|
| 10      | 0.000000709 | 0.000000416 | 0.000000875 | 0.000007083 |
| 100     | 0.000020459 | 0.000010250 | 0.000010458 | 0.000086625 |
| 1,000   | 0.00164225  | 0.000928875 | 0.000150292 | 0.000877792 |
| 10,000  | 0.112561    | 0.0707288   | 0.00175804  | 0.00942542  |
| 100,000 | 11.4583     | 7.08054     | 0.0238397   | 0.094873    |

## Conclusions

For small lists (10 ints), as expected, all 4 algorithms were extremely fast. For lists of 100, the same could be said, this time heap sort usually getting ahead.

After this, the difference became much more noticable. Selection and Insertion sort were significantly slower due to their time complexity of O(n^2). With 100,000 elements, Selection Sort took ~11 seconds and Insertion Sort took ~7 seconds.

Since Heap Sort and Merge Sort have a time complexity of O(nlogn), they scaled much better to longer lists. Heap Sort was consistently faster however, likely because merge sort's space complexity is O(n) due to it requiring more memory (uses temp vectors) than heap sort with a time complexity of O(1). 

Overall, this shows the importance of your choice of sorting algorithm as size increases. For small lists a simple algorithm like selection sort could be fine, but using an algorithm with nlogn time complexity like heap sort and merge sort could save you a lot of time. 



# Extra Credit

For this part of the assignment, I researched the AlphaDev Algorithm.

I watched this video: https://www.youtube.com/watch?v=WnOfx3iBtAo and read the article: https://www.nature.com/articles/s41586-023-06004-9. A summary of the paper is below:

## Abstract:
AlphaDev is a deep reinforcement learnign system designed to discover faster computer algorithms by building them directly from Assembly rather than the higher level C++ code. Has been successful in finding algorthms that outperform himan designed versions so far, and is promising in fields other than sorting. 

## Main: 
* Humans have already heavily optimized sorting, so finding improvement is pretty difficult
* Small sorts are important because they're used over and over again in big algorithms
* Paper focuses on fixed sorts (always sort same number of items) and variable sorts (handle different input sizes)
* AlphaDev is an extension of AlphaZero, a well known Deep Reinforcement Learning Model
* Turned algorithm discovery into AsseblyGame, where AlphaDev builds the assembly programs instruction by instruction

### Representing Algorithms as low-level CPU Instructions
AlphaDev works in x86 assembly (can optimize exact instructions executed by the CPU). Builds algorithm by choosing instructions like moves, comparisons, and junmps. 

### DRL for discovering faster algorithms
* Formulate optimizing algorithms as the CPU instruction level as an RL problem. AlphaDev treats writing an algorithm like playing AssemblyGame
  * State: Current program and register state
  * Action: Add another legal assembly instruction 
  * The reward is based on correctness and speed
This uses DRL (deep reinforcement learning) and a Monte Carlo Tree Search with the goal of finding a program thats correct and low latency

###### Transformer Encoder
Encodes assembly instructions written by AlphaDev and helps the model understand the structure of the current program. 

###### Latency Value Functions
Predicts program correctness and latency, helping optimze actual CPU speed and not just the number of instructions

## Results 
###### Discovering Faster sort algorithms
AlphaDev created sorting algorithms from scratch and many were faster than the human designed benchmarks. 

###### Fixed Sorting Algorithms
Tested Sort3, Sort4, and Sort5. Beat humans for 3 and 5, and matched for 4. Also improved Sort6-8

###### Variable Sorting Algorithms
Tested VarSort3, VarSort4, and VarSort5 and found low latency solutions, but also shows that actual latency matters more than just minimizing the instruction count since this was a more complex problem that involved branching.  

###### New Algorithm Discoveries 
AlphaDev was able to find new low-level optimization tricks such as AlphaDev Swap Move and AlphaDev Copy Move, reusing information from previous comparisons to remove unnecessary instructions. 

###### New variable sort algorithms
AlphaDev found a different structure reducing program length and latency for VarSort4. It sorts the first 3 values first, then if a 4th value exists, use a simplified sort4. 

###### Stochastic search optimization approaches
Paper compared AlphaDev with AlphaDev-S which randomly changes the program to improve them. Found that AlphaDev was better when starting from scratch and searched fewer programs, while AlphaDev-S got stuck in local optima. 

###### Generalization to additional domains
Also tested if this works outside of sorting on Google VarInt decoding. Found a branchless implementation 3x faster for single-value inputs. Promising for non sorting algorithms. 

###### Libc++ sort patch
Implemented findings into the C++ libc++ sorting library. 70% faster for some length-5 inputs and 1.7% faster for very large arrays. 

## Discussion 
The main conclusion is that reinforcement learning is useful for filling gaps humans missed. This could also be applied to other areas of research. Could also combine RL with stochastic search in the future. 

## Methods
###### Background
* AlphaZero --> What AlphaDev is Based on
* Sorting Networks --> Fixed sequence of comparisons and swaps. Very fast in small sorting problems and is what AlphaDev was trying to beat

###### Action pruning Rules (Used to shrink search space)
1. Memory locations are always read in incremental order.
2. Registers are allocated in incremental order.
3. We cannot compare or conditionally move to a memory location (illegal).
4. We can read and write to each memory location only once.
5. We cannot use non-initialized registers (illegal).
6. Do not perform consecutive compare instructions.

* Training Regime --> Trained on TPUs, up to 1mil iterations (worst case training took around 2 days)
* AlphaDev-S --> Stochastic-Search comparison method which randomly changes programs, optimizing correctness and program length. Cannot efficiently optimize actual latency during training. 
* Correctness Cost --> Measures how incorrect a sorting program
* Program Transformations --> Add/swap instructions, change opcodes and operands

###### Investigative Studies for AlphaDev Variants 
Fixed Sort
* Used for branchless fixed sorts, fewer instructions = lower latency
* AlphaDev beat a cold start stochastic search (but a warm start could match AlphaDev)

Brute Force Approach
* Used to test how exhaustive search is
* Sort3 required searching 10^23 programs (took 3 days)
* Does not scale wel

Latency Benchmarking Suite
  1. The RL agent processes 1,000 measurements across the machines using the replicated service.
  2. For each measurement, the service runs the given sorting algorithm over 10,000 random inputs (for example, for sort 3 this would be 3 × 10,000 = 30,000 random integers).
  3. We measure the time taken using a CPU performance counter (CPU_CLK_UNHALTED.CORE).

Variable Sort
* AlphaDev beat stochastic search on VarSort3–5
* Again, shows instruction count and latency aren't always correlated when branching exists

###### Exploration Hypothesis
* Stochastic search tends to get stuc near the starting solution
* Can get stuck in local optima
* AlphaDev explores more diverese programs
* Its value function helps guide it toward better solutions

###### Related Work
* Assembly Optimization
* SIMD optimization
* RL approaches for program synthesis
* Input-output examples for program synthesis 
* Deep Learning for Code Generation
* Sort-based program Optimization

