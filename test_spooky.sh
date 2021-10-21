#!/bin/bash
/usr/bin/time --format='It took %e seconds' ./wordSearch2D -p test_cases/spooky_puzzle.txt -l 50 -w test_cases/spooky_words.txt
diff output.txt test_cases/spooky_solution.txt