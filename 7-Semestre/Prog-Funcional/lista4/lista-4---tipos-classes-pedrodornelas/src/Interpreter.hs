{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
module Interpreter where

import qualified Data.Map as M
import Syntax
import Parser

mapEval :: (Int -> Int -> Int) -> Maybe Int -> Maybe Int -> Maybe Int
mapEval f (Just x) (Just y) = Just $ f x y
mapEval f _ _ = Nothing

-- 1
eval :: Expr -> Maybe Int
eval (Div _ (Num 0)) = Nothing
eval (Num x) = Just x
-- eval (Add (Num x) (Num y)) = Just (x+y)
eval (Add x y) = mapEval (+) (eval x) (eval y)
-- eval (Sub (Num x) (Num y)) = Just (x-y)
eval (Sub x y) = mapEval (-) (eval x) (eval y)
-- eval (Mult (Num x) (Num y)) = Just (x*y)
eval (Mult x y) = mapEval (*) (eval x) (eval y)
-- eval (Div (Num x) (Num y)) = Just (div x y)
eval (Div x y) = mapEval div (eval x) (eval y)

mapEvalStr :: (Expr -> Maybe Int) -> Maybe Expr -> Maybe Int
mapEvalStr f (Just x) = f x
mapEvalStr f _ = Nothing

-- 2
evalStr :: String -> Maybe Int
evalStr x = mapEvalStr eval (parseString x)

-- 6
type Env = M.Map String Int

evalV :: Env -> Expr -> Maybe Int
evalV = undefined
