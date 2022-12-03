# My own cat &amp;&amp; grep implementation 

## General info 

Implementation of GNU `cat` and BSD `grep` with all major flags and flags combinations.

## Goal & requirements

The goal of this project was to learn & replicate the functionality of the GNU cat & 
BSD grep, including all major flags and their combinations. There must be integration tests
that compare original programs with our versions.

## Key learnings
- Working with regular expressions in C
- Files IO in C
- Errno & error handling in C
- grep / cat usage knowledge
- PCRE syntax
- Working with `argv / argc`, CLI args parsing


## Build

```
$ cd cat/
$ make
$ cd grep/
$ make
```

## S21_cat

### s21_cat Usage

`$ s21_cat [OPTION] [FILE]...`

### s21_cat Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $  |
| 3 | -n (GNU: --number) | number all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeeze multiple adjacent blank lines |
| 5 | -t implies -v (GNU: -T the same, but without implying -v) | but also display tabs as ^I  |

### s21_cat integration tests

s21_cat fully replicates original GNU cat functionality, including all flags and flags combinations. 

Integration tests are launched via python script 'test.py'. Before launching tests s21_cat executable must be built. 

```
$ python3 cat/test.py
```

## S21_grep

### s21_grep Usage

`s21_grep [options] template [file_name]`

### s21_grep Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | pattern |
| 2 | -i | Ignore uppercase vs. lowercase.  |
| 3 | -v | Invert match. |
| 4 | -c | Output count of matching lines only. |
| 5 | -l | Output matching files only.  |
| 6 | -n | Precede each matching line with a line number. |

### s21_grep integration tests:

s21_grep replicated major BSD grep (2.5.1-FreeBSD) flags and their combinations listed above. s21_grep uses regex engine provided by the developers of `regex.h`.

Integration tests are launched via python script 's21_grep_tests.py'. Before launching tests s21_grep executable must be built.

```
$ python3 grep/s21_grep_tests.py
```

## Credits
- Developer: [Eltats Dunyamaliev (@eltats)](https://github.com/eltats)
- School21 for providing this task as a part of our curriculum 
