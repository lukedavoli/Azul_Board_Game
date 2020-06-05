The following are a list of numbered test cases, followed by a list
of numbered tests, each listing the test cases covered by it.
Listed test cases are all that are intentional, however tests will
most likely cover additional test cases inadvertently.

----------
TEST CASES
----------
01. AI plays a move that perfectly fills a row when appropriate
02. AI plays a move that fills a row to one less than capacity when appropriate
03. AI plays a move that fills a row to one more than capacity when appropriate
04. AI plays a move that fills a row to two or more below capacity when appropriate
05. AI plays a move that fills a row to two or more above capacity when appropriate
06. AI plays a move directly to the broken row

-----
TESTS
-----
1. 1, 4
2. 2
3. 3
4. 5
5. 6

---------
RUN TESTS
---------
./azul <Testing/aiTests/1commands.in
./azul <Testing/aiTests/2commands.in
./azul <Testing/aiTests/3commands.in
./azul <Testing/aiTests/4commands.in
./azul <Testing/aiTests/5commands.in

(running the dos2unix commands only necessary if expected file has been changed
since the last run of tests)
dos2unix Testing/aiTests/1expected.out
dos2unix Testing/aiTests/2expected.out
dos2unix Testing/aiTests/3expected.out
dos2unix Testing/aiTests/4expected.out
dos2unix Testing/aiTests/5expected.out


diff Testing/aiTests/1expected.out Testing/aiTests/1actual.out
diff Testing/aiTests/2expected.out Testing/aiTests/2actual.out
diff Testing/aiTests/3expected.out Testing/aiTests/3actual.out
diff Testing/aiTests/4expected.out Testing/aiTests/4actual.out
diff Testing/aiTests/5expected.out Testing/aiTests/5actual.out
