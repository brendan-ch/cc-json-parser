# JSON Parser

[Coding Challenges - Build Your Own JSON Parser](https://codingchallenges.fyi/challenges/challenge-json-parser)

A not-quite-finished JSON parser which can determine if a file is valid or invalid JSON.

## To-do

- [ ] Pass all additional test cases
- [ ] Build a proper lexer instead of a raw string parser
- [ ] Print useful information for debugging invalid JSON

## How to run

With `g++` installed, run the `make` command in the root directory and run the executable.

```
make
./main <filepath>
```

To run against a directory of tests under `tests`, run the executable with the `tests` argument:

```
./main tests <directory under tests>
```

