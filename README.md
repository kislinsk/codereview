# codereview

This is a tiny C++ project that is intended to be reviewed to demonstrate basic C++ and programming knowledge.

Here are a few hints before you begin with the code review:
- Ignore the fact that all code is written within a single file
- Try to follow good C++ practices like const-correctness or usage of the Standard Library
- Check if you can simplify code for example by using modern C++ features
- Consider possible bugs, error handling, documentation, or API design in general
- Prefer consistency
- ...

## Program output

You do not need to build and execute this program for code review. The output of this program is as follows:

    Alice
      Balance : 100
      Agreed overdraft: -1000
    Bob
      Balance : 0
      Agreed overdraft: -500
    Withdraw 1000 from Alice's account...
      Balance before: 100
      Balance after: -900
    Withdraw 1000 from Bob's account...
      Balance before: 0
      Balance after: -1000
    Could not find Mr. X's account!
    Alice
      Balance : 100
      Agreed overdraft: -1000
    Bob
      Balance : 0
      Agreed overdraft: -500

## Build instructions

You really do not need to build and execute this project for code review. If you would like to do so nevertheless, continue reading.

### Build with CMake

We provide a fully functional CMake script to configure and generate a build system for this project:

    git clone https://github.com/kislinsk/codereview.git
    cmake -S codereview -B codereview-build
    cmake --build codereview-build

You can explicitly specify a generator by adding the `-G` argument to the second command above, for example:

    cmake -S codereview -B codereview-build -G "Unix Makefiles"

Or on Windows something like:

    cmake -S codereview -B codereview-build -G "Visual Studio 17 2022"

### Build without CMake

The program consists of a single C++ source file without any dependencies except the C++ Standard Library. You can also manually set up your build system or IDE of choice in case you do not feel comfortable with CMake.
