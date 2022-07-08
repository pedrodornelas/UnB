{-# LANGUAGE GADTs #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
module AParser where

import Data.Char
import Control.Applicative

-- newtype Parser a where
--   P :: (String -> Maybe (a, String)) -> Parser a
newtype Parser a = P (String -> Maybe (a, String))

runParser :: Parser a -> String -> Maybe (a, String)
-- f :: (String -> Maybe (a, String))
runParser (P f) = f

satisfy :: (Char -> Bool) -> Parser Char
satisfy p = P f
  where
    f [] = Nothing  
    f (x:xs)        
                    
                    
        | p x       = Just (x, xs)
        | otherwise = Nothing

char :: Char -> Parser Char
char c = satisfy (== c)

posInt :: Parser Integer
posInt = P f
  where
    f xs
      | null ns   = Nothing
      | otherwise = Just (read ns, rest)
      where (ns, rest) = span isDigit xs

-- Item 1

instance Functor Parser where
  -- fmap :: (a -> b) -> Parser a -> Parser b
  -- (String -> Maybe (a, String)) -> (String -> Maybe (b, String))
  fmap g (P f) = P $ \str ->
    case runParser (P f) str of
      Nothing -> Nothing
      Just (a, rest) -> Just (g a, rest)

-- Item 2

instance Applicative Parser where
  -- pure :: a -> f a
  pure a = P $ \str -> Just (a, str)

  -- (<*>) :: f(a -> b) -> f a -> f b
  (<*>) p1 p2 = P $ \str ->
    case runParser p1 str of
      Nothing -> Nothing
      Just (fab, rest) ->
        case runParser p2 rest of
          Nothing -> Nothing
          Just (a, rest1) -> Just (fab a, rest1)

-- Item 3

abParser :: Parser (Char, Char)
abParser = (,) <$> char 'a' <*> char 'b'

tuple :: Char -> Char -> ()
--tuple 'a' 'b' = ()
tuple x y = ()

abParser_ :: Parser ()
-- abParser_ = P $ \str ->
--   case runParser abParser str of
--     Nothing -> Nothing
--     Just (('a','b'), rest) -> Just ((), rest)
abParser_ = tuple <$> char 'a' <*> char 'b'

mklist :: Integer -> Char -> Integer -> [Integer]
--mklist x ' ' y = [x,y]
mklist x space y = [x,y]

intPair :: Parser [Integer]
intPair = mklist <$> posInt <*> char ' ' <*> posInt


-- Item 4

instance Alternative Parser where
  -- empty :: f a
  -- empty = P $ \str -> Nothing
  empty = P $ const Nothing

  -- (<|>) :: f a -> f a -> f a
  (<|>) p1 p2 = P $ \str ->
    case runParser p1 str of
      Just x -> Just x
      Nothing -> runParser p2 str
          
    
-- Item 5

tuple1 :: a -> ()
tuple1 x = ()

upper :: Parser Char
upper = satisfy isUpper

intOrUpperCase :: Parser ()
intOrUpperCase = tuple1 <$> posInt <|> tuple1 <$> upper
-- intOrUpperCase = pure () <$> posInt <|> pure () <$> upper
-- intOrUpperCase = () <$ posInt <|> () <$ upper
