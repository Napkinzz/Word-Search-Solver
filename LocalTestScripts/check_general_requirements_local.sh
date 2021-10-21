#!/bin/bash

# Checks that assignment files exist, Makefile works, and
# files are pushed to git

readonly ERROR="\e[31;1mERROR:\x1b[0m"
readonly WARNING="\e[33;1mWARNING:\x1b[0m"
readonly SUCCESS="\e[92msuccess!\x1b[0m"
readonly EXE=wordSearch2D
readonly SOURCE=wordSearch2D.c
readonly REPO_FILES=("*akefile" "$SOURCE" "puzzle2D.c" \
  "puzzle2D.h" "puzzle.txt" "wordlist.txt" "expected_soln.txt" "sample_test.sh")

# Check for README
if [ ! -f README ] && [ ! -f ReadMe ] && [ ! -f README.md ] && [ ! -f ReadMe.md ]
then
    echo -e $ERROR "Could not find README (or any acceptable variations of it)"
    exit 1
fi

# Check for makefile and make
if [ ! -f makefile ] && [ ! -f Makefile ]
then
    echo -e $ERROR "Could not find makefile. Exiting script"
    exit 1
fi

# Check for wordSearch2D.c
if [ ! -f wordSearch2D.c ]
then
    echo -e $ERROR "Could not find $SOURCE. Exiting script"
    exit 2
fi

# Check for puzzle2D.c
if [ ! -f puzzle2D.c ]
then
    echo -e $ERROR "Could not find puzzle2D.c. Exiting script"
    exit 2
fi

# Check for puzzle2D.h
if [ ! -f puzzle2D.h ]
then
    echo -e $ERROR "Could not find puzzle2D.h. Exiting script"
    exit 2
fi

# Check for sample_test.sh
if [ ! -f sample_test.sh ]
then
  echo -e $ERROR "Could not find sample_test.sh. Exiting script"
  exit 2
fi


# Check existence of every file...
for file in ${REPO_FILES[@]}
do
    if [ ! -f $file ]
    then
        echo -e $ERROR "Could not find $file"
        exit 1
    fi
done

echo ""


# Try to make (-B will force make)
make_error=false
output="$(make -B 2>&1)"
make_result=$?

if grep "warning:" <<<"${output}"; then
    echo -e $ERROR "Your program compiles with warnings. Please fix before submitting."
    make_error=true
    exit 2
fi

if [ $make_result -ne 0 ]
then
    echo -e $ERROR "make failed. Your program does not compile correctly."
    make_error=true
    exit 2
fi

# Check that executable exists
if [ ! -f $EXE ]
then
    echo -e $ERROR "Could not find $EXE in order to run it (either your program did not compile or you have a different executable name in your Makefile)"
    make_error=true
    exit 2
fi

if [ "$make_error" = false ]
then
    echo -e "make ..." $SUCCESS
fi

echo ""

# Check make clean
clean_error=false
make clean
if [ $? -ne 0 ]
then
    echo -e $ERROR "make clean failed"
    clean_error=true
fi

if [ -f $EXE ]
then
    echo -e $ERROR "make clean should remove $EXE"
    clean_error=true
fi

if [ "$clean_error" = false ]
then
    echo -e "make clean ..." $SUCCESS
fi
echo ""

# Check existence of README in repo. Doesn't check if there are more than one
readmes=$(git ls-files {README,ReadMe}{.md,})
if [ -z $readmes ]
then
    echo -e $WARNING "Your ReadMe file (or any acceptable variation of it) is not tracked by git"
fi

# Check existence of every file (except README) in repo...
for file in ${REPO_FILES[@]}
do
    git ls-files --error-unmatch $file > /dev/null 2>&1
    if [ $? -ne 0 ]
    then
        echo -e $WARNING "$file not tracked by git"
    fi
done

# Check for new files that haven't been committed
git diff --cached --exit-code > /dev/null
new_files=$?

# Check that there are no uncommitted changes
git diff --exit-code > /dev/null
changed_files=$?

if [ $new_files -ne 0 ] || [ $changed_files -ne 0 ]
then
    echo -e $WARNING "there are uncommitted changes"
fi

# Check for unpushed changes
git diff --exit-code origin/master..HEAD > /dev/null
if [ $? -ne 0 ]
then
    echo -e $WARNING "there are unpushed commits"
fi
