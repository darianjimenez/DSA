# Lempel-Ziv Results
Below are the results of testing my implementation on various files. 

| Input file | Original size | Compressed size | Decrease in Size |
|:-----------|:--------------|:----------------|:-----------------|
| GreatGatsby.txt          | 299765 bytes | 166101 bytes | 44.59% |
| LifeontheMississippi.txt | 843430 bytes | 478088 bytes | 43.32% |
| lorem-ipsum.txt          | 2949 bytes | 2924 bytes     | 0.85%  |
| numbers.txt              | 28657 bytes | 21881 bytes   | 23.65% |
| txt_sample_file_1MB.txt  | 1048668 bytes | 47723 bytes | 95.45% |
| txt_sample_file_2MB.txt  | 2097220 bytes | 99449 bytes | 95.26% | 
| words-list.txt           | 40737 bytes | 28722 bytes   | 29.49% |

From my results for the encoder, it looks like, as expected, lempel-ziv works best with files that have a lot of repetitive text like the random sample files I had. It didn't work as well with the words list since it had many unique words (same goes for the numbers list). Since lorem ipsum was already a small file it looks like it couldn't do much. Lastly, it worked really well on the books, likely because language tends to have many repetitive phrases which lempel ziv is able to take advantage of. 

My decoder was also able to successfully decode all my files back to their original state and all my unit tests passed. 