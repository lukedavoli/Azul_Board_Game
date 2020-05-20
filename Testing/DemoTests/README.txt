The following are a list of numbered test cases, followed by a list
of numbered tests, each listing the test cases covered by it.
Listed test cases are all that are intentional, however tests will
most likely cover additional test cases inadvertently. The number in
square brackets denotes the seed used.

----------
TEST CASES
----------
01. Valid turn to row 1
02. Valid turn to row 2
03. Valid turn to row 3
04. Valid turn to row 4
05. Valid turn to row 5
06. Valid turn to broken storage
07. Invalid turn, storage row below range
08. Invalid turn, storage row above range
09. Invalid turn, storage row character rather than number (not B)
10. Invalid turn, two characters for factory
11. Invalid turn, two characters for tile
12. Invalid turn, two characters for storage row
13. Invalid turn, factory below range
14. Invalid turn, factory above range
15. Invalid turn, factory a character rather than number
16. Invalid turn, tile doesn't exist
17. Invalid turn, number rather than character
18. Invalid turn, attempted to store in full row 1
19. Invalid turn, attempted to store in full row 2
20. Invalid turn, attempted to store in full row 3
21. Invalid turn, attempted to store in full row 4
22. Invalid turn, attempted to store in full row 5
23. Invalid turn, attempted to store in row 1 occupied by another colour
24. Invalid turn, attempted to store in row 2 occupied by another colour
25. Invalid turn, attempted to store in row 3 occupied by another colour
26. Invalid turn, attempted to store in row 4 occupied by another colour
27. Invalid turn, attempted to store in row 5 occupied by another colour
28. Invalid turn, attempted to store in row 1, colour complete in mosaic
29. Invalid turn, attempted to store in row 2, colour complete in mosaic
30. Invalid turn, attempted to store in row 3, colour complete in mosaic
31. Invalid turn, attempted to store in row 4, colour complete in mosaic
32. Invalid turn, attempted to store in row 5, colour complete in mosaic
33. Valid turn, stored in row 1 with overflow into broken
34. Valid turn, stored in row 2 with overflow into broken
35. Valid turn, stored in row 3 with overflow into broken
36. Valid turn, stored in row 4 with overflow into broken
37. Valid turn, stored in row 5 with overflow into broken
38. Valid turn, overflow from row to broken to box lid
39. Invalid turn, tile does not exist in factory 0
40. Invalid turn, tile does not exist in factory 1
41. Invalid turn, tile does not exist in factory 2
42. Invalid turn, tile does not exist in factory 3
43. Invalid turn, tile does not exist in factory 4
44. Invalid turn, tile does not exist in factory 5
45. Points calculated correctly for single tile
46. Points calculated correctly for consecutive vertical tiles
47. Points calculated correctly for consecutive horizontal tiles
48. Points calculated correctly for consecutive vertical and horizontal tiles
49. Player holding F tile has active turn in next round
50. Factories refilled correctly following end of round
51. Box lid refilled sequentially from tile bag
52. Bonus points calculated correctly for complete column at end of game
53. Bonus points calculated correctly for complete row at end of game
54. Bonus points calculated correctly for complete set of a colour at end of game
55. First player to take from central factory takes F tile

-----
TESTS
-----
1[45]: 01, 02, 03, 04, 05, 55
2[23]: 06, 07, 08, 09
3[76]: 10, 11, 12
4[91]: 13, 14, 15, 16, 17
5[56]: 18, 19, 20, 21
6[72]: 22, 23, 24, 25, 26, 27
7[69]: 28, 29, 30, 31, 32
8[10]: 33, 34, 35, 36