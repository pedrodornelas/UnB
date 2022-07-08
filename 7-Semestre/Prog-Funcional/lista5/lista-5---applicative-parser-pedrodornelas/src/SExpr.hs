{-# LANGUAGE GADTs #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
module SExpr where

import AParser
import Data.Char
import Control.Applicative
import Test.Hspec (shouldMatchList)
import Text.Printf (PrintfArg(parseFormat))

type Ident = String

data Atom where
  N :: Integer -> Atom
  I :: Ident   -> Atom
  deriving (Eq, Show)

data SExpr where
  A    :: Atom    -> SExpr
  Comb :: [SExpr] -> SExpr
  deriving (Eq, Show)

-- Item 6
mklist1 :: a -> [a]
mklist1 x = [x]

mklist2 :: a -> [a]
mklist2 x = []

zeroOrMore :: Parser a -> Parser [a]
zeroOrMore x = ((++) <$> (mklist1 <$> x) <*> zeroOrMore x) <|> pure []
-- zeroOrMore x = P $ \str ->
--   case runParser (oneOrMore x) str of
--     Nothing -> Just ([], str) == pure []
--     Just x -> Just x


oneOrMore :: Parser a -> Parser [a]
oneOrMore x = ((++) <$> (mklist1 <$> x) <*> oneOrMore x) <|> (mklist1 <$> x)

-- Item 7

spaces :: Parser String
spaces = zeroOrMore (satisfy isSpace)


isAlpha' :: Parser Char
isAlpha' = satisfy isAlpha

isAlphaNum' :: Parser Char
isAlphaNum' = satisfy isAlphaNum

ident :: Parser String
ident = ((++) <$> (mklist1 <$> isAlpha') <*> oneOrMore isAlphaNum') <|> (mklist1 <$> isAlpha')

-- Item 8

intToSExpr :: Integer -> SExpr
intToSExpr x = A (N x)

parseInt :: Parser SExpr
parseInt = intToSExpr <$> posInt

stringToSExpr :: String -> SExpr
stringToSExpr x = A (I x)

parseIdent :: Parser SExpr
parseIdent = stringToSExpr <$> ident

ignoreSpaces :: Parser [String]
ignoreSpaces = mklist1 <$> spaces

parseAtom :: Parser SExpr
parseAtom = ignoreSpaces *> (parseInt <|> parseIdent)

isComb :: Parser Char
isComb = ignoreSpaces *> satisfy ( =='(' )

mkComb :: Char -> [SExpr] -> SExpr
mkComb x = Comb

ignoreBracket :: Parser Char
ignoreBracket = satisfy (== ')')

parseComb :: Parser SExpr
parseComb = mkComb1 <$> oneOrMore (mkComb <$> isComb <*> oneOrMore parseAtom <* ignoreBracket)

mkComb1 :: [SExpr] -> SExpr
mkComb1 [Comb x] = Comb x
mkComb1 x = Comb x

parseSExpr :: Parser SExpr
parseSExpr = parseComb <|> parseAtom
















































-- mkComb :: SExpr -> SExpr
-- mkComb x = Comb [x]

-- isBracket :: Char -> Bool
-- isBracket '(' = True
-- isBracket _ = False

-- isComb :: Parser Char
-- isComb = satisfy isBracket

-- parseSExpr :: Parser SExpr
-- -- parseSExpr = isComb <$> parseAtom
-- -- parseSExpr = (mkComb <$> parseAtom) <|> parseAtom
-- parseSExpr = P $ \str ->
--   case runParser isComb str of
--     Nothing -> runParser parseAtom str
--     Just (a, rest) -> runParser (oneOrMore (mkComb <$> parseAtom)) rest

