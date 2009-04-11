import Data.List
import System.Environment (getArgs)


wordFile = "/home/jml/Dropbox/Code/Scrabble/source_data/sowpods.txt"

isShuffledSublist bigger (x:xs) | x `elem` bigger = isShuffledSublist (delete x bigger) xs
                                | otherwise = False
isShuffledSublist _ _ = True

fitsTarget targetWord central word =
    and [wordLength >= 4,
         wordLength <= targetWordLength,
         central `elem` word,
         isShuffledSublist targetWord word]
    where
      wordLength = length word
      targetWordLength = length targetWord


doTargetSearch :: String -> String -> IO ()
doTargetSearch targetWord (central : []) =
    readFile wordFile >>= putStrLn . unlines . filter predicate . words
    where predicate = fitsTarget targetWord central



main = do
  arguments <- getArgs
  case arguments of
    [targetWord, central] -> doTargetSearch targetWord central
    _ -> putStrLn "./Target <target_word> <central_char>"
