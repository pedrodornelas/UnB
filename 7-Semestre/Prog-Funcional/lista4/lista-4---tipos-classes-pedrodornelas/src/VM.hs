{-# LANGUAGE TypeSynonymInstances #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
module VM where

import Syntax
import Display
import Test.Hspec (xcontext)
import Data.Foldable (find)
import Control.Monad.Cont (cont)
import Data.Map (mapAccum)
import System.IO (openBinaryTempFileWithDefaultPermissions)
import Data.Type.Bool (Not)

data Bytecode = PUSH Int
              | ADD
              | SUB
              | MULT
              | DIV
              deriving (Eq, Show)

-- 4
compile :: Expr -> [Bytecode]
compile (Num x) = [PUSH x]
compile (Add x y) = compile x ++ compile y ++ [ADD]
compile (Sub x y) = compile x ++ compile y ++ [SUB]
compile (Mult x y) = compile x ++ compile y ++ [MULT]
compile (Div x y) = compile x ++ compile y ++ [DIV]


mapMaybe :: (a -> Maybe b) -> Maybe a -> Maybe b
mapMaybe f Nothing = Nothing
mapMaybe f (Just x) = f x

-- 5
runBytecode :: [Bytecode] -> Maybe Int
runBytecode [] = Nothing
runBytecode [PUSH x] = Just x
runBytecode [_] = Nothing
runBytecode (x:xs) = mapMaybe runBytecode (operation (x:xs))

mapOperation :: (a -> a -> a) -> Maybe a -> Maybe a -> Maybe a -> Maybe a
mapOperation (++) (Just x) (Just y) (Just z) = Just $ x ++ y ++ z
mapOperation _ _ _ _ = Nothing

mapPos :: (Num a , Ord a)=> (a -> a -> a) -> Maybe a -> a -> Maybe a
mapPos f (Just x) y
    | f x y < 0 = Nothing
    | otherwise = Just $ f x y
mapPos _ _ _ = Nothing


operation :: [Bytecode] -> Maybe [Bytecode]
operation (x:xs) = mapOperation (++) initOfStack (stack x1 x2 op) finalOfStack 
    where
        pos = posOperation 0 (x:xs)
        initOfStack  = initStack (mapPos (-) pos 2) [] (x:xs)
        finalOfStack = finalStack pos (x:xs)
        x1 = getBytecode (mapPos (-) pos 2) (x:xs)
        x2 = getBytecode (mapPos (-) pos 1) (x:xs)
        op = getBytecode  pos               (x:xs)

posOperation :: Int -> [Bytecode] -> Maybe Int
posOperation cont ((PUSH x):xs) = posOperation (cont+1) xs
posOperation cont (x:xs) = Just cont
posOperation _ _ = Nothing

initStack :: Maybe Int -> [Bytecode] -> [Bytecode] -> Maybe [Bytecode]
initStack Nothing _ _ = Nothing
initStack (Just 0) init xs = Just init
initStack (Just pos) init (x:xs) = initStack (Just (pos-1)) (init ++ [x]) xs

finalStack :: Maybe Int -> [Bytecode] -> Maybe [Bytecode]
finalStack Nothing _ = Nothing
finalStack (Just 0) (x:xs) = Just xs
finalStack (Just pos) (x:xs) = finalStack (Just (pos-1)) xs

getBytecode :: Maybe Int -> [Bytecode] -> Maybe Bytecode
getBytecode Nothing _ = Nothing
getBytecode (Just 0) (x:xs) = Just x
getBytecode (Just cont) (x:xs) = getBytecode (Just (cont-1)) xs


stack :: Maybe Bytecode -> Maybe Bytecode -> Maybe Bytecode -> Maybe [Bytecode]
stack (Just (PUSH x)) (Just (PUSH y)) (Just op)
    | op == ADD  = Just [PUSH (x+y)]
    | op == SUB  = Just [PUSH (x-y)]
    | op == MULT = Just [PUSH (x*y)]
    | op == DIV  = Just [PUSH (div x y)]
stack _ _ _ = Nothing