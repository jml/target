// Solves "Target" word puzzles.
//
// The Target puzzle is one where nine letters are arranged in a grid.  Your
// goal is to find as many words as you can that can be made out of those
// letters and include the central letter.
//
// Words must be four or more characters long, and plurals aren't allowed
// (although this code isn't smart enough to figure out what's a plural).

package main

import "bufio"
import "flag"
import "fmt"
import "os"
import "strings"


const WordFile = "/home/jml/src/Scrabble/source_data/sowpods.txt"


func SearchDictionary(targetWord, centralChar string) {
	file, err := os.Open(WordFile)
	if err != nil {
		panic(err)
	}
	buffered := bufio.NewReader(file)
	fmt.Printf("Searching dictionary for %q sub-anagrams around %q\n", targetWord, centralChar)
	for {
		line, isPrefix, error := buffered.ReadLine()
		if isPrefix {
			panic("Don't know how to handle line buffer overflows")
		}
		if error == os.EOF {
			break
		}
		word := string(line)
		if FitsTarget(targetWord, centralChar, word) {
			fmt.Println(word)
		}
	}
}


// Is 'string' a sub-anagram of 'targetWord'?
//
// That is, is it possible to rearrange the letters of 'string' and
// 'targetWord' such that the letters of the former are a substring of the
// letters of the latter?
//
// In Python:
//     duplicate = list(target_word)
//     for c in word:
//         if c not in duplicate:
//             return False
//         duplicate.remove(c)
//     return True
func IsSubAnagram(targetWord, word string) bool {
	duplicate := targetWord[:]
	for _, wordChar := range word {
		match := strings.Index(duplicate, string(wordChar))
		if match == -1 {
			return false
		}
		duplicate = duplicate[:match] + duplicate[match+1:]
	}
	return true
}


// Is 'word' a valid match for our target?
func FitsTarget(targetWord, centralChar, word string) bool {
	switch {
	case len(word) < 4:
		return false
	case len(word) > len(targetWord):
		return false
	case !strings.Contains(word, centralChar):
		return false
	case !IsSubAnagram(targetWord, word):
		return false
	default:
		return true
	}
	return true
}


func main() {
	flag.Parse()
	if flag.NArg() != 2 {
		fmt.Printf("%v <target_word> <central_character>\n", os.Args[0])
		os.Exit(1)
	}
	targetWord := flag.Arg(0)
	if len(targetWord) != 9 {
		fmt.Printf("target_word must have exactly 9 letters: %v\n", targetWord)
		os.Exit(1)
	}
	centralChar := flag.Arg(1)
	if len(centralChar) != 1 {
		fmt.Printf("central_character must have exactly 1 letter: %v\n", centralChar)
		os.Exit(1)
	}
	SearchDictionary(strings.ToUpper(targetWord), strings.ToUpper(centralChar))
}
