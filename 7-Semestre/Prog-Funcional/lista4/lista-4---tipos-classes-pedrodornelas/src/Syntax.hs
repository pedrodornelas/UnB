{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
module Syntax where

import Display

data Expr = Num  Int
          | Var  String
          | Add  Expr Expr
          | Sub  Expr Expr
          | Mult Expr Expr
          | Div  Expr Expr
          deriving (Eq, Show)

-- 3
instance Display Expr where
  -- display :: Expr -> String
  display (Num x) = show x
  display (Add x y) = "(" ++ display x ++ " + " ++ display y ++ ")"
  display (Sub x y) = "(" ++ display x ++ " - " ++ display y ++ ")"
  display (Mult x y) = "(" ++ display x ++ " * " ++ display y ++ ")"
  display (Div x y) = "(" ++ display x ++ " / " ++ display y ++ ")"
