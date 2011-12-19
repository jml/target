import Data.List
import Data.Word
import qualified Data.ByteString.Lazy as B
import System.Environment (getArgs)
import System.IO


wordFile = "/home/jml/Dropbox/Code/Scrabble/source_data/sowpods.txt"

isShuffledSublist bigger (x:xs) | x `elem` bigger = isShuffledSublist (delete x bigger) xs
                                | otherwise = False
isShuffledSublist _ _ = True


c2w :: Char -> Word8
c2w = fromIntegral . fromEnum

newline = c2w '\n'
byteLines = B.split newline
byteUnlines = B.intercalate (B.pack [newline])


fitsTarget :: [Word8] -> Word8 -> B.ByteString -> Bool
fitsTarget targetWord central word =
    and [wordLength >= 4,
         wordLength <= fromIntegral targetWordLength,
         central `B.elem` word,
         isShuffledSublist targetWord (B.unpack word)]
    where
      wordLength = B.length word
      targetWordLength = length targetWord


doTargetSearch :: String -> String -> IO ()
doTargetSearch targetWord (central : []) =
    B.readFile wordFile >>= B.putStrLn . byteUnlines . filter predicate . byteLines
    where predicate = fitsTarget (map c2w targetWord) (c2w central)


main = do
  arguments <- getArgs
  case arguments of
    [targetWord, central] -> doTargetSearch targetWord central
    _ -> putStrLn "./Target <target_word> <central_char>"
