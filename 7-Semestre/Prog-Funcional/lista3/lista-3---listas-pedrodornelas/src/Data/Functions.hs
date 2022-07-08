module Data.Functions where

import Prelude hiding (sequence)
import GHC.Base (VecElem(DoubleElemRep))

-- Parte 1

member :: Eq a => a -> [a] -> Bool
member x [] = False
--member x (y:ys) = if x==y then True else member x ys
member x (y:ys) = x==y || member x ys

count :: (Num a, Eq b) => b -> [b] -> a
count x [] = 0 
--count x (y:ys) = if x==y then count x ys + 1 else count x ys
count x (y:ys)
    | x==y = count x ys + 1
    | otherwise = count x ys

forall :: (a -> Bool) -> [a] -> Bool
forall p [] = False
forall p [y] = p y
--forall p (y:ys) = if p y then forall p ys else False
forall p (y:ys)
    | p y = forall p ys
    | otherwise = False

exists :: (a -> Bool) -> [a] -> Bool
exists p [] = False
--exists p (y:ys) = if p y then True else exists p ys
exists p (y:ys) = p y || exists p ys

first :: (a -> Bool) -> [a] -> Maybe a
first p [] = Nothing
--first p (y:ys) = if p y then Just y else first p ys
first p (y:ys)
    | p y = Just y
    | otherwise = first p ys

single :: (a -> Bool) -> [a] -> Bool
single p [] = False
--single p (y:ys) = if p y then not (single p ys) else single p ys
single p (y:ys)
    | p y = not (single p ys)
    | otherwise = single p ys

mostly :: (a -> Bool) -> [a] -> Bool
mostly p [] = False
mostly p (y:ys) = aux p (y:ys) > div (length (y:ys)) 2 where
    aux :: (a -> Bool) -> [a] -> Int
    aux p [] = 0
    --aux p (y:ys) = if p y then aux p ys + 1 else aux p ys
    aux p (y:ys)
        | p y = aux p ys + 1
        | otherwise = aux p ys

mostlyTrue :: [Bool] -> Bool
mostlyTrue = mostly (== True)

-- Parte 2

majority :: Eq a => [a] -> Maybe a
majority [] = Nothing
majority [x] = Just x
majority (x:xs) = tupla x 1 xs where
    tupla :: (Eq a) => a -> Int -> [a] -> Maybe a
    tupla x 0 [] = Nothing
    tupla x n [] = Just x
    --tupla x n (y:ys) = if x==y then tupla x (n+1) ys 
    --                   else 
    --                    (if n>=1 then tupla x (n-1) ys else tupla y 1 ys)
    tupla x n (y:ys)
        | x == y = tupla x (n+1) ys
        | n >= 1 = tupla x (n-1) ys
        | otherwise = tupla y 1 ys


collatz1 :: Int -> Int
collatz1 1 = 1
collatz1 n
    | even n = div n 2
    | otherwise = (3*n)+1

-- collatz :: Int -> [Int]
-- collatz n = constList n [] where
--     constList :: Int -> [Int] -> [Int]
--     constList 1 ys = ys ++ [1]
--     constList n ys = constList (collatz1 n) (ys ++ [n])

collatz :: Int -> [Int]
collatz 1 = [1]
collatz n = n:collatz (collatz1 n)

isFixpoint :: Eq a => (a -> a) -> a -> Bool
isFixpoint f x = f x == x

-- findFixpoint :: Eq a => (a -> a) -> a -> Int -> Maybe a
-- findFixpoint f x limit
--     | limit > 0 = aplica f x limit 
--     | otherwise = Nothing 
--     where
--         aplica :: Eq a => (a -> a) -> a -> Int -> Maybe a
--         aplica f x limit
--             | isFixpoint f x = Just x
--             | otherwise = findFixpoint f (f x) (limit-1)

findFixpoint :: Eq a => (a -> a) -> a -> Int -> Maybe a
findFixpoint f x limit
    | limit > 0 && isFixpoint f x = Just x
    | limit > 0 = findFixpoint f (f x) (limit-1)
    | otherwise = Nothing

testCollatzConjecture :: Int -> [Int] -> [Bool]
testCollatzConjecture limit [] = []
testCollatzConjecture limit (y:ys) = (findFixpoint collatz1 y limit == Just 1):(testCollatzConjecture limit ys)

tooBig :: Double -> Bool
tooBig x = x > 0.0001

nearlyEqual :: Double -> Double -> Bool
nearlyEqual 0 0 = True
nearlyEqual x y
    | y == 0 = False -- x não pode ser 0, e 0/x==0 para qualquer x
    | 0.9999 <= x/y && x/y <= 1.0001 = True
    | otherwise = False

sequence :: (Int -> Double) -> Int -> [Double]
sequence f i = f i:sequence f (i+1)

-- series :: (Int -> Double) -> Int -> [Double]
-- series f i = f i:constList f (i+1) (f i) where
--     constList :: (Int -> Double) -> Int -> Double -> [Double]
--     constList f i sumAnt = (f i + sumAnt):constList f (i+1) (f i + sumAnt)

series :: (Int -> Double) -> Int -> [Double]
series f i = f i:constList f (i+1) (f i) where
    constList :: (Int -> Double) -> Int -> Double -> [Double]
    constList f i sumAnt = (f i + sumAnt):constList f (i+1) (f i + sumAnt)

seriesLimit :: (Int -> Double) -> Int -> [Double]
seriesLimit f i = f i:constList f (i+1) (f i) where
    constList :: (Int -> Double) -> Int -> Double -> [Double]
    constList f i sumAnt
        | tooBig (abs (f i)) = (f i + sumAnt):constList f (i+1) (f i + sumAnt)
        | otherwise = [f i + sumAnt]

-- Ln2 = [1/1-1/2+1/3-1/4+1/5-...]
computeLn2 :: Double
computeLn2 = last $ seriesLimit termoLn2 0

termoLn2 :: Int -> Double
termoLn2 n = ((-1)^fromIntegral n)/(fromIntegral n+1)

computeE :: Double
computeE = last $ seriesLimit termoE 0

termoE :: Int -> Double
termoE n = 1 / fromIntegral (factorial n)

factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial (n-1)

computePsi :: Double
computePsi = last $ seriesLimit termoPsi 0

termoPsi :: Int -> Double
termoPsi n = 1 / fromIntegral (fibonacci n) 

fibonacci :: Int -> Int
fibonacci 0 = 1
fibonacci 1 = 1
fibonacci n = fibonacci (n-1) + fibonacci (n-2)